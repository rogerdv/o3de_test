#pragma once

#include "BaseItem.h"

namespace keyw {

	class ItemWeapon : public BaseItem
	{
	public:
		AZ_RTTI(ItemWeapon, "{6BC3486F-104A-4F22-A5D4-0CD014E49CEE}");
		ItemWeapon();
		~ItemWeapon();
		static void Reflect(AZ::ReflectContext* context);

		void Equip();

		AZStd::array<float, 5> Dmg;
	private:

	};

}