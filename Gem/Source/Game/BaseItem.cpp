
#include "BaseItem.h"

namespace keyw {
	
	BaseItem::BaseItem() {
		Id = "";
		Durability = 100.0f;
	}

	void BaseItem::Reflect(AZ::ReflectContext* context) {
		if (auto sc = azrtti_cast<AZ::SerializeContext*>(context)) {
			sc->Class<BaseItem>()
				->Version(1)
				->Field("Id", &BaseItem::Id)
				->Field("Category", &BaseItem::Category)
				->Field("ItemType", &BaseItem::ItemType)
				->Field("PrefabAsset", &BaseItem::PrefabAsset);
		}
		
		AZ::BehaviorContext* behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context);
		if (behaviorContext) {
			behaviorContext->Class<BaseItem>("BaseItem")
				->Property("Id", BehaviorValueProperty(&BaseItem::Id))
				->Property("Category", BehaviorValueProperty(&BaseItem::Category))
				->Property("PrefabAsset", BehaviorValueProperty(&BaseItem::PrefabAsset))
				->Method("Equip", &Equip);
		}
		
	}

	/*Equip the item in a character*/
	void BaseItem::Equip() { //AZ::EntityId owner
		AZ_Printf("BaseItem", "I have been equipped!!");
	}

	/*Use the item on a target*/
	void BaseItem::Use() { //AZ::EntityId owner, AZ::EntityId target
		AZ_Printf("BaseItem", "Using %s", Id.c_str());
	}

}
