
#pragma once

#include <keyw/keywTypeIds.h>

#include <AzCore/EBus/EBus.h>
#include <AzCore/RTTI/BehaviorContext.h>
#include <AzCore/Interface/Interface.h>

namespace keyw
{
    class keywRequests
    {
    public:
        AZ_RTTI(keywRequests, keywRequestsTypeId);
        virtual ~keywRequests() = default;
        // Put your public methods here        
        virtual void InitItemDb() = 0;
        virtual BaseItem *GetItem(AZStd::string ItemId) = 0;
        virtual void RegisterPlayerAvatar(AZ::EntityId id) = 0;
        virtual AZ::EntityId GetPlayerAvatar() = 0;
    };

    class keywBusTraits
        : public AZ::EBusTraits
    {
    public:
        //////////////////////////////////////////////////////////////////////////
        // EBusTraits overrides
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
        //////////////////////////////////////////////////////////////////////////
    };

    using keywRequestBus = AZ::EBus<keywRequests, keywBusTraits>;
    using keywInterface = AZ::Interface<keywRequests>;

    //Notification bus
    class keywNotifications : public AZ::EBusTraits
    {
    public:
        AZ_RTTI(keywNotifications, "{CF8D1F59-FDC4-48A0-9EB9-DA7E5B3B4A79}");
        virtual ~keywNotifications()=default;
        //! EBus Trait: save data notifications are addressed to a single address
        static const AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;

        //! EBus Trait: save data notifications can be handled by multiple listeners
        static const AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Multiple;

        virtual void OnPlayerRegister() = 0;
    };
    using keywNotificationBus = AZ::EBus<keywNotifications>;

} // namespace keyw
