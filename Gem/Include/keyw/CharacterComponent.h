#pragma once

#include <keyw/CharacterComponentBus.h>
#include <AzCore/Component/Component.h>
#include <AzCore/Component/EntityBus.h>
#include <AzCore/Component/TickBus.h>
#include <AzCore/Math/Vector3.h>


namespace keyw {
	
	//Attribute indexes
	const int STR = 0;
	const int INT = 1;
	const int DEX = 2;
	const int CON = 3;
	const int CHR = 4;

	// Any game character, NPC or player
	class CharacterComponent : public AZ::Component, public CharacterComponentBus::Handler, 
		public AZ::TickBus::Handler
	{
	public:
		AZ_COMPONENT(CharacterComponent,
			"{ABDAE29E-789F-4B98-9B6E-D238A769F2CC}");

		// AZ::Component overrides
		void Activate() override;
		void Deactivate() override;

		// Provide runtime reflection, if any
		static void Reflect(AZ::ReflectContext* reflection);

		static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& io_provided);
		static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& io_incompatible);

		// AZ::TickBus
		void OnTick(float i_deltaTime, AZ::ScriptTimePoint i_time) override;

		//Character stuff
		AZStd::string Name;
		AZStd::array<int, 5> attribs = { 10,10,10,10,10 };
		int Level = 1;
		//int attribs[5] = {10,10,10,10,10};


		float HP[2];
		float EP[2];

		AZStd::string GetName();
		//Returns the total attribute value, considering base and bonus and penalties
		int GetAttribute(int attr);
		void RecalcDerivedStats();
		float GetCurrentHP();
		float GetMaxHP();
		int GetLevel() { return Level; };

	private:
		bool Dead = false;
		float Timer = 0.0f;
		

	};
	
}