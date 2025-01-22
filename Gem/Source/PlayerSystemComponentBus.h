#pragma once

#include <AzCore/EBus/EBus.h>
#include <AzCore/Interface/Interface.h>

namespace keyw {
	class PlayerSystemComponentRequests
	{
	public:
		AZ_RTTI(PlayerSystemComponentRequests, "{48F90AFE-0E25-414F-8961-1F443919E9BB}");
		
		virtual ~PlayerSystemComponentRequests() = default;

		virtual void UpdateAvatar() = 0;
		virtual void SetPlayerEntity(AZ::EntityId pId) = 0;

	private:

	}; //class

	class PlayerSystemComponentEBusTraits: public AZ::EBusTraits
	{
	public:
		// EBusTraits overrides
		static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;
		static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;

	private:

	}; //class

	using PlayerSystemComponentRequestsBus = AZ::EBus<PlayerSystemComponentRequests, PlayerSystemComponentEBusTraits>;
	using PlayerSystemComponentInterface = AZ::Interface<PlayerSystemComponentRequests>;

	class PlayerSystemComponentNotifications : public AZ::EBusTraits
	{
	public:
		//! EBus Trait: save data notifications are addressed to a single address
		static const AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;

		//! EBus Trait: save data notifications can be handled by multiple listeners
		static const AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Multiple;		
	};
	using PlayerSystemComponentNotificationBus = AZ::EBus<PlayerSystemComponentNotifications>;
	
} //namespace