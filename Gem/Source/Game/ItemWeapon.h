#pragma once

#include "BaseItem.h"
#include <AzFramework/Spawnable/Spawnable.h>
#include <AzFramework/Spawnable/Script/SpawnableScriptMediator.h>
#include <AzFramework/Spawnable/Script/SpawnableScriptNotificationsHandler.h>
#include <AzFramework/Spawnable/SpawnableEntitiesInterface.h>
#include <AzFramework/Asset/AssetCatalog.h>


namespace keyw {

	class ItemWeapon : public BaseItem, protected AzFramework::Scripts::SpawnableScriptNotificationsBus::Handler
	{
	public:
		AZ_RTTI(ItemWeapon, "{6BC3486F-104A-4F22-A5D4-0CD014E49CEE}");
		ItemWeapon();
		~ItemWeapon();
		static void Reflect(AZ::ReflectContext* context);

		void Equip(AZ::EntityId owner);

		void OnSpawn(AzFramework::EntitySpawnTicket ticket, AZStd::vector<AZ::EntityId> entityList);

		AZStd::array<float, 5> Dmg;
		AZStd::string EquipScript;

		AzFramework::Scripts::SpawnableScriptMediator mediator;
		AzFramework::EntitySpawnTicket SpawnTicket;

	private:
		

	};

}