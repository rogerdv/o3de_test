
#include "keyw/CharacterComponent.h"
#include <AzCore/Serialization/EditContextConstants.inl>

namespace keyw {

	void CharacterComponent::Reflect(AZ::ReflectContext* reflection) {
		if (auto sc = azrtti_cast<AZ::SerializeContext*>(reflection)) {
			sc->Class<CharacterComponent, AZ::Component>()
				->Version(0)
				->Field("Attributes", &CharacterComponent::attribs)
				->Field("Name", &CharacterComponent::Name)
				->Field("Level", &CharacterComponent::Level)
				;

			if (AZ::EditContext* ec = sc->GetEditContext())
			{
				ec->Class<CharacterComponent>("CharacterComponent", "Game character data")
					->ClassElement(AZ::Edit::ClassElements::EditorData, "")
					->Attribute(AZ::Edit::Attributes::AppearsInAddComponentMenu, AZ_CRC("Game"))
					->Attribute(AZ::Edit::Attributes::AutoExpand, true)
					//Attributes
					->ClassElement(AZ::Edit::ClassElements::Group, "")
					->Attribute(AZ::Edit::Attributes::AutoExpand, true)

					->DataElement(AZ::Edit::UIHandlers::Default, &CharacterComponent::attribs, "Attributes", "")
					//Name
					->ClassElement(AZ::Edit::ClassElements::Group, "")
					->Attribute(AZ::Edit::Attributes::AutoExpand, true)

					->DataElement(AZ::Edit::UIHandlers::Default, &CharacterComponent::Name, "Name", "")
					//Lvl
					->ClassElement(AZ::Edit::ClassElements::Group, "")
					->Attribute(AZ::Edit::Attributes::AutoExpand, true)

					->DataElement(AZ::Edit::UIHandlers::Default, &CharacterComponent::Level, "Level", "")
					;
			}
		};
		
		if (AZ::BehaviorContext* behaviorContext = azrtti_cast<AZ::BehaviorContext*>(reflection)) {
			behaviorContext->EBus<CharacterComponentBus>("CharacterComponentBus")
				->Event("GetAttribute", &CharacterComponentBus::Events::GetAttribute)
				->Event("GetName", &CharacterComponentBus::Events::GetName)
				->Event("RecalcDerivedStats", &CharacterComponentBus::Events::RecalcDerivedStats)
				->Event("GetCurrentHP", &CharacterComponentBus::Events::GetCurrentHP)
				->Event("GetMaxHP", &CharacterComponentBus::Events::GetMaxHP);
			behaviorContext->Constant("STR", BehaviorConstant(STR))
				->Constant("INT", BehaviorConstant(INT));
			
		}
	}

	void CharacterComponent::Activate() {
		CharacterComponentBus::Handler::BusConnect(m_entity->GetId());
		AZ::TickBus::Handler::BusConnect();
		RecalcDerivedStats();
	}

	void CharacterComponent::Deactivate() {
		CharacterComponentBus::Handler::BusDisconnect();
		AZ::TickBus::Handler::BusDisconnect();
		
	}

	void CharacterComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& io_provided)
	{
		io_provided.push_back(AZ_CRC_CE("CharacterComponent"));
	}

	void CharacterComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& io_incompatible)
	{
		io_incompatible.push_back(AZ_CRC_CE("CharacterComponent"));
	}

	void CharacterComponent::OnTick(float i_deltaTime, [[maybe_unused]] AZ::ScriptTimePoint i_time) {
		if (Dead)
			return;
		
		if (HP[0] <= 0.0f) {
			//Character is dead
			Dead = true;
		}

		Timer = Timer + i_deltaTime;
		if (Timer > 1.0f) {
			Timer = 0.0f;
			//Do regeneration
			if (HP[0] < HP[1]) {
				//regenerate hit points
				HP[0] = HP[0] + GetAttribute(CON) / 100;
			}
		}
	}

	int CharacterComponent::GetAttribute(int attr) {
		
		return attribs[attr];
	}

	//REcalculate values like HP and such
	void CharacterComponent::RecalcDerivedStats() {
		HP[0] = attribs[STR]*2.0f + attribs[CON] * 3.0f; 
		HP[1] = HP[0];
	}

	float CharacterComponent::GetCurrentHP() {
		return HP[0];
	}
	
	float CharacterComponent::GetMaxHP() {
		return HP[1];
	}
	
	AZStd::string CharacterComponent::GetName() {
		return Name;
	}
}