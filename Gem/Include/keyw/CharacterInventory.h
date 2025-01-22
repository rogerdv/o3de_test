#pragma once

#include <keyw/CharacterInventoryBus.h>
#include <AzCore/Component/Component.h>
#include <AzCore/Component/EntityBus.h>

#include <AzCore/std/string/string.h>


#include "Game/BaseItem.h"
#include <keyw/keywBus.h>


namespace keyw {
	//contains an item in the actual character inventory, and its amount
	struct InvElement
	{
		AZStd::string ElementId;	//Unique id of this inventory element 
		BaseItem *item;
		int amount = 1;	//if stackable, amount of items of same type, like a potion

	};

	class CharacterInventory: public AZ::Component, public CharacterInventoryBus::Handler
	{
	public:
		AZ_COMPONENT(CharacterInventory,
			"{8B4DDA5E-A303-4A8C-B92E-E000E344F65F}");
		
		// AZ::Component overrides
		void Activate() override;
		void Deactivate() override {}

		// Provide runtime reflection, if any
		static void Reflect(AZ::ReflectContext* reflection);
		
		static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& io_provided);
		static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& io_incompatible);

		void ReceiveItem(const AZStd::string& ItemId);
		void EquipByIndex(AZStd::string ItemId, AZ::EntityId owner);
		AZ::EntityId GetSlotAttach([[maybe_unused]] int SlotIndex);
		//void EquipById(AZStd::string ItemId);
		int TotalWeight();

		AZStd::vector<InvElement*> items;
		//Slots
		AZStd::unordered_map<AZStd::string, AZStd::string> EquipSlots;
		AZStd::array<AZ::EntityId, 9> AttachPoints;
		

	private:

	};
}