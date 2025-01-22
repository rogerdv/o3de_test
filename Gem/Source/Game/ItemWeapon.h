#pragma once

#include "BaseItem.h"
#include <AzFramework/Spawnable/Spawnable.h>
#include <AzFramework/Spawnable/Script/SpawnableScriptMediator.h>
#include <AzFramework/Spawnable/SpawnableEntitiesInterface.h>
#include <AzFramework/Asset/AssetCatalog.h>


namespace keyw {

	class ItemWeapon : public BaseItem
	{
	public:
		AZ_RTTI(ItemWeapon, "{6BC3486F-104A-4F22-A5D4-0CD014E49CEE}");
		ItemWeapon();
		~ItemWeapon();
		static void Reflect(AZ::ReflectContext* context);

		void Equip(AZ::EntityId owner);

		AZStd::array<float, 5> Dmg;
		AZStd::string EquipScript = "assets/scripts/EquipTest.lua";

		AzFramework::Scripts::SpawnableScriptMediator mediator;
		AzFramework::EntitySpawnTicket SpawnTicket;

	private:
		

	};

}