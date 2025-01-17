#pragma once

#include "BaseItem.h"
namespace keyw {

	class ItemArmor : public BaseItem

	{
	public:
		AZ_RTTI(ItemArmor, "{957C9681-3CED-4AB0-A098-7DF11FD945B0}");
		ItemArmor();
		~ItemArmor();

		static void Reflect(AZ::ReflectContext* context);

		void Equip(AZ::EntityId owner);

		AZStd::array<int, 5> Protection;
	private:

	};

}