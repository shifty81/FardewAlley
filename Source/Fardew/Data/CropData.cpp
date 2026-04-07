#include "CropData.h"

namespace Fardew
{
    void CropDatabase::Register(const CropDefinition& definition)
    {
        m_Definitions[definition.Id] = definition;
    }

    const CropDefinition* CropDatabase::Find(CropId id) const
    {
        const auto it = m_Definitions.find(id);
        return it != m_Definitions.end() ? &it->second : nullptr;
    }

    const CropDefinition* CropDatabase::FindBySeed(ItemId itemId) const
    {
        for (const auto& [id, definition] : m_Definitions)
        {
            (void)id;
            if (definition.SeedItemId == itemId)
            {
                return &definition;
            }
        }
        return nullptr;
    }
}
