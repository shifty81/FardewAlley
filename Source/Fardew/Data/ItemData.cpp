#include "ItemData.h"

namespace Fardew
{
    void ItemDatabase::Register(const ItemDefinition& definition)
    {
        m_Definitions[definition.Id] = definition;
    }

    const ItemDefinition* ItemDatabase::Find(ItemId id) const
    {
        const auto it = m_Definitions.find(id);
        return it != m_Definitions.end() ? &it->second : nullptr;
    }

    bool ItemDatabase::IsStackable(ItemId id) const
    {
        const ItemDefinition* definition = Find(id);
        return definition != nullptr && definition->MaxStack > 1;
    }
}
