
#include "BaseItem.h"

namespace keyw {
	
	class ItemNotificationsBusBehaviorHandler
		: public ItemNotificationsBus::Handler
		, public AZ::BehaviorEBusHandler
	{
	public:
		////////////////////////////////////////////////////////////////////////////////////////////
		AZ_EBUS_BEHAVIOR_BINDER(ItemNotificationsBusBehaviorHandler, "{28AE78B0-D220-4A52-B523-934FF1F7B36A}", AZ::SystemAllocator
			, OnItemEquipped, OnItemUsed
		);

		////////////////////////////////////////////////////////////////////////////////////////////
		void OnItemEquipped(AZStd::string item) override {
			Call(FN_OnItemEquipped, item);
		}

		void OnItemUsed(AZStd::string item, AZ::EntityId owner, AZ::EntityId target) override {
			Call(FN_OnItemUsed, item, owner, target);
		}
	};

	BaseItem::BaseItem() {
		Id = "";
		Durability = 100.0f;
	}

	void BaseItem::Reflect(AZ::ReflectContext* context) {
		if (auto sc = azrtti_cast<AZ::SerializeContext*>(context)) {
			sc->Class<BaseItem>()
				->Version(1)
				->Field("Id", &BaseItem::Id)
				->Field("Category", &BaseItem::Category)
				->Field("ItemType", &BaseItem::ItemType)
				->Field("PrefabAsset", &BaseItem::PrefabAsset);
		}
		
		AZ::BehaviorContext* behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context);
		if (behaviorContext) {
			behaviorContext->Class<BaseItem>("BaseItem")
				->Property("Id", BehaviorValueProperty(&BaseItem::Id))
				->Property("Category", BehaviorValueProperty(&BaseItem::Category))
				->Property("PrefabAsset", BehaviorValueProperty(&BaseItem::PrefabAsset))
				->Property("TestSc", BehaviorValueProperty(&BaseItem::TestSc))
				->Method("Equip", &Equip)
				->Method("Equip", &Use);
			//Request Bus
			behaviorContext->EBus<ItemRequestBus>("ItemRequestBus")
				->Event("ItemEquipped", &ItemRequestBus::Events::ItemEquipped)
				->Event("TotalWeight", &ItemRequestBus::Events::ItemUsed)	;
			//Notification bus
			behaviorContext->EBus<ItemNotificationsBus>("ItemNotificationsBus")
				->Handler<ItemNotificationsBusBehaviorHandler>();
		}
		
	}

	/*Equip the item in a character*/
	void BaseItem::Equip([[maybe_unused]] AZ::EntityId owner) { //AZ::EntityId owner
		AZ_Printf("BaseItem", "I have been equipped!!");		
	}

	/*Use the item on a target*/
	void BaseItem::Use([[maybe_unused]] AZ::EntityId owner, [[maybe_unused]] AZ::EntityId target) { //AZ::EntityId owner, AZ::EntityId target
		AZ_Printf("BaseItem", "Using %s", Id.c_str());
	}

}
