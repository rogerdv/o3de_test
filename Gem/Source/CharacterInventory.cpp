#include "keyw/CharacterInventory.h"
#include <AzCore/Serialization/EditContext.h>

namespace keyw {

	class InventoryNotificationsBusBehaviorHandler
		: public InventoryNotificationsBus::Handler
		, public AZ::BehaviorEBusHandler
	{
	public:
		////////////////////////////////////////////////////////////////////////////////////////////
		AZ_EBUS_BEHAVIOR_BINDER(InventoryNotificationsBusBehaviorHandler, "{4FC448DC-2C7B-4361-AD5A-C342BC6E4A72}", AZ::SystemAllocator
			, OnItemEquipped, OnItemUsed
		);

		////////////////////////////////////////////////////////////////////////////////////////////
		void OnItemEquipped(AZStd::string item, AZ::EntityId owner) override {
			Call(FN_OnItemEquipped, item, owner);
		}

		void OnItemUsed(AZStd::string item, AZ::EntityId owner, AZ::EntityId target) override {
			Call(FN_OnItemUsed, item, owner, target);
		 }
	};

	void CharacterInventory::Reflect(AZ::ReflectContext* reflection)
	{
		
		if (auto sc = azrtti_cast<AZ::SerializeContext*>(reflection)) {
			sc->Class<CharacterInventory, AZ::Component>()
				->Version(1)
				->Field("AttachmentPoints", &CharacterInventory::AttachPoints);

			if (AZ::EditContext* ec = sc->GetEditContext())
			{
				ec->Class<CharacterInventory>("Inventory", "[Manages character inventory]")
					->ClassElement(AZ::Edit::ClassElements::EditorData, "")
					->Attribute(AZ::Edit::Attributes::AppearsInAddComponentMenu, AZ_CRC("Game"))
					->Attribute(AZ::Edit::Attributes::AutoExpand, true)
					//Attach points
					->ClassElement(AZ::Edit::ClassElements::Group, "")
					->Attribute(AZ::Edit::Attributes::AutoExpand, true)
					->DataElement(AZ::Edit::UIHandlers::Default, &CharacterInventory::AttachPoints, "Attachment points", "");
					
			}
		};
		
		if (AZ::BehaviorContext* behaviorContext = azrtti_cast<AZ::BehaviorContext*>(reflection)) {
			behaviorContext->EBus<CharacterInventoryBus>("CharacterInventoryBus")
				->Event("ReceiveItem", &CharacterInventoryBus::Events::ReceiveItem)
				->Event("TotalWeight", &CharacterInventoryBus::Events::TotalWeight)
				->Event("EquipByIndex", &CharacterInventoryBus::Events::EquipByIndex)
				->Event("GetSlotAttach", &CharacterInventoryBus::Events::GetSlotAttach);

			behaviorContext->EBus<InventoryNotificationsBus>("InventoryNotificationsBus")
			    ->Handler<InventoryNotificationsBusBehaviorHandler>();
		}
	}

	void CharacterInventory::Activate() {
		CharacterInventoryBus::Handler::BusConnect(m_entity->GetId());
	}

	void CharacterInventory::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& io_provided)
	{
		io_provided.push_back(AZ_CRC_CE("CharacterInventory"));
	}

	void CharacterInventory::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& io_incompatible)
	{
		io_incompatible.push_back(AZ_CRC_CE("CharacterInventory"));
	}

	//Adds an item to the inventory
	void CharacterInventory::ReceiveItem(const AZStd::string& ItemId) {
		//Check if item already exists
		for (const auto& element : items) {
			if (element->ElementId == ItemId) {
				//already exists
				if (element->item->Stack) {
					element->amount++;
					return;
				}

			}//if element
		} //for
		//Item not in inventory or is not stackable
		InvElement* elem=new InvElement();
		elem->ElementId = ItemId;
		elem->item = new BaseItem();
		
		keywRequestBus::BroadcastResult(elem->item, &keywRequestBus::Events::GetItem, ItemId);
		
		//AZ_Printf("ItemLoader", "Received Item ID: %s", elem->item->Id.c_str());
		items.push_back(elem);	

	}

	void CharacterInventory::EquipByIndex(AZStd::string ItemIndex, AZ::EntityId owner) {
		//AZ_Printf("Inventory", "Equip %s in entity %d==%d", ItemIndex.c_str(), GetEntityId(), owner);
		//first, find the item
		for (const auto& element : items) {
			if (element->ElementId == ItemIndex) {
				//found
				if (EquipSlots[element->item->Slot] != "") {
					//TODO, unequip
				}
				EquipSlots[element->item->Slot] = element->ElementId;
				element->item->Equip(owner);
			}
		}
	}

	//Returns total weight in inventory
	int CharacterInventory::TotalWeight() {
		int weight = 0;
		for (const auto& element : items) {
			//AZ_Printf("Inventory", "Item: %s, weight: %d", element->item->Id.c_str(), element->item->Weight);
			weight=weight+element->item->Weight*element->amount;
		}
		//AZ_Printf("Inventory", "Total weigth counted: %d", weight);
		return weight;		
	}

	//Temporary, return first attachment always
	AZ::EntityId CharacterInventory::GetSlotAttach([[maybe_unused]] int SlotIndex) {
		for (int i = 0; i < 9;i++) {
			AZ_Printf("Inventory", "Slot entity # %d id: %d", i, AttachPoints[i]);
		}
		return AttachPoints[SlotIndex];
	}

	/*BaseItem* CharacterInventory::GetItem(AZStd::string ItemIndex) {
		for (const auto& element : items) {
			if (element->ElementId == ItemIndex) {
				return element->item;
			}
	}*/
	

}