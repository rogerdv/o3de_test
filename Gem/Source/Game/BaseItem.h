#pragma once

#include <AzCore/EBus/EBus.h>
#include <AzCore/RTTI/BehaviorContext.h>
#include "keyw/CharacterInventoryBus.h"
#include <AzCore/std/string/string.h>


namespace keyw {

	//Request bus
	class ItemRequests
	{
	public:
		AZ_RTTI(ItemRequests, "{A43C3647-75DE-4F8F-9B27-A2ACF80FE289}");
		virtual ~ItemRequests() = default;
		// Put your public methods here        
		virtual void ItemEquipped(AZStd::string item) = 0;
		virtual void ItemUsed(AZStd::string item, AZ::EntityId target) = 0;
	};

	class ItemBusTraits
		: public AZ::EBusTraits
	{
	public:
		//////////////////////////////////////////////////////////////////////////
		// EBusTraits overrides
		static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Multiple;
		static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::ById;
		using BusIdType = AZ::EntityId;
		//////////////////////////////////////////////////////////////////////////
	};

	using ItemRequestBus = AZ::EBus<ItemRequests, ItemBusTraits>;
	//using ItemInterface = AZ::Interface<ItemRequests>;

	//Notification bus
	class ItemNotifications : public AZ::EBusTraits
	{
	public:
		AZ_RTTI(ItemNotifications, "{E3D3572A-7CC6-4A0B-9E0E-2D753799449F}");
		virtual ~ItemNotifications() = default;

		virtual void OnItemEquipped(AZStd::string item) = 0;
		virtual void OnItemUsed(AZStd::string item, AZ::EntityId owner, AZ::EntityId target) = 0;
	
		//! EBus Trait: save data notifications are addressed to an Id
		static const AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::ById;
		using BusIdType = AZ::EntityId;

		//! EBus Trait: save data notifications can be handled by multiple listeners
		static const AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Multiple;

		
	};
	using ItemNotificationsBus = AZ::EBus<ItemNotifications>;

	/* This class handles common item properties*/
	class BaseItem: protected ItemRequestBus::Handler {
	public:
		AZ_RTTI(BaseItem, "{1AD6FB80-B5FA-43D2-8939-B4EE7AED752A}");
		
		BaseItem();
		virtual ~BaseItem() {};

		static void Reflect(AZ::ReflectContext* context);

		virtual void Equip(AZ::EntityId owner);
		virtual void Use(AZ::EntityId owner, AZ::EntityId target);

		//Request bus
		void ItemEquipped([[maybe_unused]] AZStd::string item) override {};
		void ItemUsed([[maybe_unused]] AZStd::string item, [[maybe_unused]] AZ::EntityId target) override {};

		//Item properties
		AZStd::string Id;
		AZ::EntityId ItemOwner;
		AZStd::string Category; //global item category (armor, consumable, weapon, component)
		AZStd::string ItemType; //Specific item type: sword, shield
		bool Equipable;
		bool Stack=false;
		AZStd::string PrefabAsset;
		AZStd::string Slot;
		AZStd::string TestSc;
		
		float Rarity;
		float Durability;
		int Weight;
		
		
	protected:
		

	};

	

	

} //namespace