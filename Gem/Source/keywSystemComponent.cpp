
#include <AzCore/Serialization/SerializeContext.h>
#include <AzCore/Serialization/EditContext.h>
#include <AzCore/Serialization/EditContextConstants.inl>
#include <AzCore/Serialization/Json/JsonSystemComponent.h>
#include <AzCore/Serialization/Json/JsonUtils.h>
#include <AzCore/Serialization/Json/RegistrationContext.h>

#include "keywSystemComponent.h"
#include "Game/ItemLoader.h"


#include <keyw/keywTypeIds.h>

namespace keyw
{
	AZ_COMPONENT_IMPL(keywSystemComponent, "keywSystemComponent",
		keywSystemComponentTypeId);

	class keywNotificationBusBehaviorHandler
		: public keywNotificationBus::Handler
		, public AZ::BehaviorEBusHandler
	{
	public:
		////////////////////////////////////////////////////////////////////////////////////////////
		AZ_EBUS_BEHAVIOR_BINDER(keywNotificationBusBehaviorHandler, "{CE11195D-BDD2-46A1-92CF-5714E0973DA1}", AZ::SystemAllocator
			, OnPlayerRegister
		);

		////////////////////////////////////////////////////////////////////////////////////////////
		void OnPlayerRegister() override {
			Call(FN_OnPlayerRegister);
		}
	};

	void keywSystemComponent::Reflect(AZ::ReflectContext* context)
	{
		if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
		{
			serializeContext->Class<keywSystemComponent, AZ::Component>()
				->Version(0)
				;
			/*serializeContext->Class<BaseItem>()
				->Version(1)
				->Field("Id", &BaseItem::Id)
				->Field("Category", &BaseItem::Category)
				->Field("ItemType", &BaseItem::ItemType)
				->Field("PrefabAsset", &BaseItem::PrefabAsset);*/
		}
		AZ::BehaviorContext* behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context);
		if (behaviorContext) {        
			behaviorContext->EBus<keywRequestBus>("keywRequestBus")				
				->Event("InitItemDb", &keywRequestBus::Events::InitItemDb)
				->Event("GetItem", &keywRequestBus::Events::GetItem)
				->Event("RegisterPlayerAvatar", &keywRequestBus::Events::RegisterPlayerAvatar)
				->Event("GetPlayerAvatar", &keywRequestBus::Events::GetPlayerAvatar);
			
			
			//Notification bus	
			behaviorContext->EBus<keywNotificationBus>("keywNotificationBus")
				->Handler<keywNotificationBusBehaviorHandler>();
				//->Event("OnPlayerRegister", &keywNotificationBus::Events::OnPlayerRegister);
		}

		//Reflect Item class
		BaseItem::Reflect(context);
		ItemWeapon::Reflect(context);
		ItemArmor::Reflect(context);
		
	}

	void keywSystemComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
	{
		provided.push_back(AZ_CRC_CE("keywService"));
	}

	void keywSystemComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
	{
		incompatible.push_back(AZ_CRC_CE("keywService"));
	}

	void keywSystemComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
	{
	}

	void keywSystemComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
	{
	}

	keywSystemComponent::keywSystemComponent()
	{
		if (keywInterface::Get() == nullptr)
		{
			keywInterface::Register(this);
		}
	}

	keywSystemComponent::~keywSystemComponent()
	{
		if (keywInterface::Get() == this)
		{
			keywInterface::Unregister(this);
		}
	}

	void keywSystemComponent::Init()
	{
	}

	void keywSystemComponent::Activate()
	{
		keywRequestBus::Handler::BusConnect();
		
	}

	void keywSystemComponent::Deactivate()
	{
		keywRequestBus::Handler::BusDisconnect();
	}

		
	void keywSystemComponent::InitItemDb()
	{
		ItemLoader itemLoader{};
		items = itemLoader.LoadItems("assets/items.json");
		for (const auto& item : items)
		{
			AZ_Printf("ItemLoader", "Item ID: %s, Cate: %s, Type: %s", item.Id.c_str(), item.Category.c_str(), item.ItemType.c_str(), item.Rarity);
		}
	}

	/*
	 Returns a copy of an item definition
	*/
	BaseItem *keywSystemComponent::GetItem(AZStd::string ItemId)
	{
		//BaseItem t;        
		for (const BaseItem& item : items)
		{
			if (item.Id == ItemId)
			{
				AZ_Printf("ItemLoader", "Found item %s", ItemId.c_str());
				if (item.Category == "weapon") {
					ItemWeapon* w = new ItemWeapon();
					w->Id = item.Id;
					w->Category = item.Category;
					w->Weight = item.Weight;
					w->PrefabAsset = item.PrefabAsset;
					return w;
				}
				else {
					BaseItem* t = new BaseItem();
					t->Id = item.Id;
					t->Category = item.Category;
					t->Weight = item.Weight;
					t->PrefabAsset = item.PrefabAsset;
					return t;

				}
				
			}            
		}
		return nullptr;
		
	}

	void keywSystemComponent::RegisterPlayerAvatar(AZ::EntityId id) { 
		PlayerAvatar = id; 
		PlayerSystemComponentRequestsBus::Broadcast(&PlayerSystemComponentRequestsBus::Events::SetPlayerEntity, id);
		//EBUS_EVENT(keywNotificationBus, OnPlayerRegister);
		keywNotificationBus::Broadcast(&keywNotificationBus::Events::OnPlayerRegister);
	}
	
}
