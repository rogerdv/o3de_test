
#include "PlayerSystemComponent.h"

namespace keyw {
	AZ_COMPONENT_IMPL(PlayerSystemComponent, "PlayerSystemComponent",
		"{3853AFFA-4EE4-4F02-B6D9-B9D8D1E5A633}");

	void PlayerSystemComponent::Reflect(AZ::ReflectContext* context)
	{
		if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
		{
			serializeContext->Class<PlayerSystemComponent, AZ::Component>()
				->Version(0);
			
		}
		AZ::BehaviorContext* behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context);
		if (behaviorContext) {
			behaviorContext->EBus<PlayerSystemComponentRequestsBus>("PlayerSystemComponentRequestsBus")
				->Event("UpdateAvatar", &PlayerSystemComponentRequestsBus::Events::UpdateAvatar)
				->Event("SetPlayerEntity", &PlayerSystemComponentRequestsBus::Events::SetPlayerEntity)
				/*->Event("InitItemDb", &keywRequestBus::Events::InitItemDb)
				->Event("GetItem", &keywRequestBus::Events::GetItem)
				->Event("RegisterPlayerAvatar", &keywRequestBus::Events::RegisterPlayerAvatar)
				->Event("GetPlayerAvatar", &keywRequestBus::Events::GetPlayerAvatar)*/;



			//behaviorContext->EBus<keywNotificationBus>("keywNotificationBus")
			  //  ->Handler<keywNotificationBusBehaviorHandler>();
		}

		

	}

	void PlayerSystemComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
	{
		provided.push_back(AZ_CRC_CE("PlayerService"));
	}

	void PlayerSystemComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
	{
		incompatible.push_back(AZ_CRC_CE("PlayerService"));
	}

	void PlayerSystemComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
	{
	}

	void PlayerSystemComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
	{
	}

	PlayerSystemComponent::PlayerSystemComponent()
	{
		if (PlayerSystemComponentInterface::Get() == nullptr)
		{
			PlayerSystemComponentInterface::Register(this);
		}
	}

	PlayerSystemComponent::~PlayerSystemComponent()
	{
		if (PlayerSystemComponentInterface::Get() == this)
		{
			PlayerSystemComponentInterface::Unregister(this);
		}
	}

	void PlayerSystemComponent::Init()
	{
	}

	void PlayerSystemComponent::Activate()
	{
		PlayerSystemComponentRequestsBus::Handler::BusConnect();

	}

	void PlayerSystemComponent::Deactivate()
	{
		PlayerSystemComponentRequestsBus::Handler::BusDisconnect();
	}

	//Events
	void PlayerSystemComponent::UpdateAvatar() {
		
	}

	void PlayerSystemComponent::SetPlayerEntity(AZ::EntityId pId) { 
		PlayerEntity = pId; 
		keywRequestBus::BroadcastResult(PlayerEntity, &keywRequestBus::Events::GetPlayerAvatar);
	}

}//namespace