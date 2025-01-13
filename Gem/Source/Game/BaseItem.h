#pragma once

#include <AzCore/std/string/string.h>


namespace keyw {
	class BaseItem {
	public:
		AZ_RTTI(BaseItem, "{1AD6FB80-B5FA-43D2-8939-B4EE7AED752A}");
		
		BaseItem();
		virtual ~BaseItem() {};

		static void Reflect(AZ::ReflectContext* context);

		virtual void Equip();
		virtual void Use();

		//Item properties
		AZStd::string Id;
		AZStd::string Category; //globa item category (armor, consumable, weapon, component)
		AZStd::string ItemType; //Specific item type: sword, shield
		bool Equipable;
		AZStd::string PrefabAsset;
		AZStd::string Slot;
		
		float Rarity;
		float Durability;
		int Weight;

	};

} //namespace