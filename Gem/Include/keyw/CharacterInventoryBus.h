#pragma once

#include <AzCore/Component/ComponentBus.h>


namespace keyw {
	class CharacterInventoryInterface: public AZ::ComponentBus
	{
	public:
		AZ_RTTI(CharacterInventoryInterface, "{171E0FA4-0E95-45E3-BEC6-269337073AAD}");
		virtual ~CharacterInventoryInterface() = default;
		
		virtual void ReceiveItem(const AZStd::string& ItemId) = 0;
		virtual int TotalWeight() = 0;

		//! Only one component on a entity can implement the events
		static const AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;
	private:

	};

	typedef AZ::EBus<CharacterInventoryInterface> CharacterInventoryBus;
	
}