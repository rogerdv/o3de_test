
#include "ItemArmor.h"

namespace keyw {

	ItemArmor::ItemArmor()
	{
	}

	ItemArmor::~ItemArmor()
	{
	}

	void ItemArmor::Reflect(AZ::ReflectContext* context) {
		AZ::BehaviorContext* behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context);
		if (behaviorContext) {
			behaviorContext->Class<ItemArmor>("ItemArmor")
			->Property("Protection", BehaviorValueProperty(&ItemArmor::Protection));

		}
	}

	void ItemArmor::Equip([[maybe_unused]] AZ::EntityId owner) {

	}

}