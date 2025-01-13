
#pragma once

#include <AzCore/Component/Component.h>

#include "Game/BaseItem.h"
#include "PlayerSystemComponentBus.h"
#include <keyw/keywBus.h>



namespace keyw
{
    class keywSystemComponent
        : public AZ::Component, 
        protected keywRequestBus::Handler
        //protected keywNotificationBus::Handler
    {
    public:
        AZ_COMPONENT_DECL(keywSystemComponent);

        static void Reflect(AZ::ReflectContext* context);

        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);

        keywSystemComponent();
        ~keywSystemComponent();

        AZStd::string LevelToLoad;
        AZ::EntityId PlayerAvatar;

    protected:
        ////////////////////////////////////////////////////////////////////////
        // keywRequestBus interface implementation        
        void InitItemDb() override;
        BaseItem *GetItem(AZStd::string ItemId) override;
        void RegisterPlayerAvatar(AZ::EntityId id) override;
        AZ::EntityId GetPlayerAvatar() override { return PlayerAvatar; };
        ////////////////////////////////////////////////////////////////////////

        //void OnPlayerRegister() override;
        ////////////////////////////////////////////////////////////////////////
        // AZ::Component interface implementation
        void Init() override;
        void Activate() override;
        void Deactivate() override;
        ////////////////////////////////////////////////////////////////////////
        AZStd::vector<BaseItem> items;
    };
}
