#pragma once

#include "../Core/FardewTypes.h"
#include <unordered_map>

namespace Fardew
{
    struct ItemDefinition
    {
        ItemId Id = 0;
        std::string Name;
        ItemCategory Category = ItemCategory::None;
        ToolType Tool = ToolType::None;
        std::uint16_t MaxStack = 1;
        std::uint32_t SellValue = 0;
        CropId PlantCropId = 0;
    };

    struct ItemStack
    {
        ItemId Id = 0;
        std::uint16_t Count = 0;

        [[nodiscard]] bool IsEmpty() const noexcept
        {
            return Id == 0 || Count == 0;
        }
    };

    class ItemDatabase
    {
    public:
        void Register(const ItemDefinition& definition);
        [[nodiscard]] const ItemDefinition* Find(ItemId id) const;
        [[nodiscard]] bool IsStackable(ItemId id) const;

    private:
        std::unordered_map<ItemId, ItemDefinition> m_Definitions;
    };
}
