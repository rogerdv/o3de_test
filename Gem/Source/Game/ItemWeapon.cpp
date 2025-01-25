
#include "ItemWeapon.h"

namespace keyw {

	ItemWeapon::ItemWeapon(){
		//BusConnect(SpawnTicket);
		
		//AzFramework::Scripts::SpawnableScriptNotificationsBus::BusConnect(SpawnTicket);
		//AzFramework::Scripts::SpawnableScriptNotificationsBus::Connect(SpawnTicket);
	}

	ItemWeapon::~ItemWeapon() {

	}

	void ItemWeapon::Reflect(AZ::ReflectContext* context) {
		//AZ_Printf("ItemWeapon", "Reflect");
		AZ::BehaviorContext* behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context);
		if (behaviorContext) {
			behaviorContext->Class<ItemWeapon>("ItemWeapon")
			->Property("Dmg", BehaviorValueProperty(&ItemWeapon::Dmg))
			->Property("EquipScript", BehaviorValueProperty(&ItemWeapon::EquipScript));
				
		}
	}

	void ItemWeapon::Equip([[maybe_unused]] AZ::EntityId owner) {
		ItemOwner = owner;
		AZ_Printf("ItemWeapon", "I have been equipped in %d!!", owner);
		AZ::Data::AssetId assetId;
		AZ::Data::AssetCatalogRequestBus::BroadcastResult(
			assetId, &AZ::Data::AssetCatalogRequestBus::Events::GetAssetIdByPath,
			PrefabAsset.c_str(), azrtti_typeid<AzFramework::Spawnable>(), false);
		AZ::Data::Asset<AzFramework::Spawnable> spawnableAsset{ AZ::Data::AssetManager::Instance().GetAsset<AzFramework::Spawnable>(
			assetId, AZ::Data::AssetLoadBehavior::PreLoad) };

		AzFramework::Scripts::SpawnableScriptAssetRef spawnableScriptAssetRef;
		spawnableScriptAssetRef.SetAsset(spawnableAsset);

		//auto spawnableSystem = AzFramework::SpawnableEntitiesInterface::Get();
		SpawnTicket = mediator.CreateSpawnTicket(spawnableScriptAssetRef); //AzFramework::EntitySpawnTicket{ spawnableAsset };
		AZ::EntityId SlotPoint; 
		CharacterInventoryBus::EventResult(SlotPoint, owner, &CharacterInventoryBus::Events::GetSlotAttach, 0);
		AZ_Printf("ItemWeapon", "Slot entity id: %d",SlotPoint);
		
		//CharacterInventoryBus::EventResult()
		mediator.SpawnAndParent(SpawnTicket, SlotPoint);
		
		//spawnableSystem->SpawnAllEntities(SpawnTicket);
		
		
		//ItemNotificationsBus::Event(owner, &ItemNotificationsBus::Events::OnItemEquipped, Id);
	}

	void ItemWeapon::OnSpawn(AzFramework::EntitySpawnTicket ticket, AZStd::vector<AZ::EntityId> entityList) {
		AZ_Printf("ItemWeapon", "Spawning, calling equip event");
		ItemNotificationsBus::Event(ItemOwner, &ItemNotificationsBus::Events::OnItemEquipped, Id);
	}

}
