#pragma once

#include <AzCore/Math/Vector3.h>

namespace keyw {
	class CharacterComponentInterface : public AZ::ComponentBus {
	public:
		AZ_RTTI(CharacterComponentInterface, "{97F49634-14E3-4C23-AC97-45F63EC56795}");
		virtual ~CharacterComponentInterface() = default;

		virtual AZStd::string GetName() = 0;
		virtual int GetAttribute(int attr) = 0;
		virtual void RecalcDerivedStats() = 0;

		virtual float GetCurrentHP() = 0;
		virtual float GetMaxHP() = 0;
		virtual int GetLevel() = 0;
		

		//! Only one component on a entity can implement the events
		static const AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;
	};

	typedef AZ::EBus<CharacterComponentInterface> CharacterComponentBus;
}