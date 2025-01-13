
#include "ItemWeapon.h"

namespace keyw {

	ItemWeapon::ItemWeapon() {

	}

	ItemWeapon::~ItemWeapon() {

	}

	void ItemWeapon::Reflect(AZ::ReflectContext* context) {
		AZ_Printf("ItemWapon", "Reflect");
		AZ::BehaviorContext* behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context);
		if (behaviorContext) {
			behaviorContext->Class<ItemWeapon>("ItemWeapon")
			->Property("Dmg", BehaviorValueProperty(&ItemWeapon::Dmg));
				
		}
	}

	void ItemWeapon::Equip() {
		AZ_Printf("ItemWeapon", "I have been equipped!!");
	}

}
