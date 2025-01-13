
#include <AzCore/Memory/SystemAllocator.h>
#include <AzCore/Module/Module.h>

#include "keywSystemComponent.h"
#include "PlayerSystemComponent.h"
#include "keyw/CharacterInventory.h"
#include "keyw/CharacterComponent.h"

#include <keyw/keywTypeIds.h>

namespace keyw
{
    class keywModule
        : public AZ::Module
    {
    public:
        AZ_RTTI(keywModule, keywModuleTypeId, AZ::Module);
        AZ_CLASS_ALLOCATOR(keywModule, AZ::SystemAllocator);

        keywModule()
            : AZ::Module()
        {
            // Push results of [MyComponent]::CreateDescriptor() into m_descriptors here.
            m_descriptors.insert(m_descriptors.end(), {
                keywSystemComponent::CreateDescriptor(),
                PlayerSystemComponent::CreateDescriptor(),
                CharacterInventory::CreateDescriptor(),
                CharacterComponent::CreateDescriptor(),
            });
        }

        /**
         * Add required SystemComponents to the SystemEntity.
         */
        AZ::ComponentTypeList GetRequiredSystemComponents() const override
        {
            return AZ::ComponentTypeList{
                azrtti_typeid<keywSystemComponent>(),
            };
        }
    };
}// namespace keyw

#if defined(O3DE_GEM_NAME)
AZ_DECLARE_MODULE_CLASS(AZ_JOIN(Gem_, O3DE_GEM_NAME), keyw::keywModule)
#else
AZ_DECLARE_MODULE_CLASS(Gem_keyw, keyw::keywModule)
#endif
