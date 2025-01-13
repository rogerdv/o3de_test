#pragma once
#include <AzCore/Component/Component.h>

#include "PlayerSystemComponentBus.h"

namespace keyw {

	class PlayerSystemComponent: public AZ::Component,
		protected PlayerSystemComponentRequestsBus::Handler
	{
	public:
		AZ_COMPONENT_DECL(PlayerSystemComponent);
		PlayerSystemComponent();
		~PlayerSystemComponent();

		static void Reflect(AZ::ReflectContext* context);

		static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
		static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);
		static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
		static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);

		AZStd::string Name;
		AZStd::array<int, 5> attribs = { 10,10,10,10,10 };
		int Level = 1;
		int Exp = 0;		//player experience
		AZ::EntityId PlayerEntity;
	private:

		////////////////////////////////////////////////////////////////////////
		// AZ::Component interface implementation
		void Init() override;
		void Activate() override;
		void Deactivate() override;
		////////////////////////////////////////////////////////////////////////

		void UpdateAvatar() override;
		void SetPlayerEntity(AZ::EntityId pId) override;

	};

	
}