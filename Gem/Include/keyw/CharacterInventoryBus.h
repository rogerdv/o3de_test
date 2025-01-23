#pragma once

#include <AzCore/Component/ComponentBus.h>


namespace keyw {
	class CharacterInventoryInterface: public AZ::ComponentBus
	{
	public:
		AZ_RTTI(CharacterInventoryInterface, "{171E0FA4-0E95-45E3-BEC6-269337073AAD}");
		virtual ~CharacterInventoryInterface() = default;
		
		virtual void ReceiveItem(const AZStd::string& ItemId) = 0;
		virtual void EquipByIndex(AZStd::string ItemIndex, AZ::EntityId owner) = 0;
		//virtual BaseItem* GetItem(AZStd::string ItemIndex) = 0;
		virtual int TotalWeight() = 0;
		virtual AZ::EntityId GetSlotAttach(int SlotIndex) = 0;

		//! Only one component on a entity can implement the events
		static const AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;
	private:

	};

	typedef AZ::EBus<CharacterInventoryInterface> CharacterInventoryBus;

	//Notification bus
	class InventoryNotifications : public AZ::EBusTraits
	{
	public:
		AZ_RTTI(InventoryNotifications, "{BD512572-70B8-495D-9B91-1688E321CADE}");
		virtual ~InventoryNotifications() = default;
		//! EBus Trait: save data notifications are addressed to a single address
		static const AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;

		//! EBus Trait: save data notifications can be handled by multiple listeners
		static const AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Multiple;

		virtual void OnItemEquipped(AZStd::string item, AZ::EntityId owner) = 0;
		virtual void OnItemUsed(AZStd::string item, AZ::EntityId owner, AZ::EntityId target) = 0;
		
	};
	using InventoryNotificationsBus = AZ::EBus<InventoryNotifications>;
	
}