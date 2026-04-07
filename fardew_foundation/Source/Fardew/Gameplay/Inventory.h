#pragma once

#include "../Data/ItemData.h"
#include <array>

namespace Fardew
{
    constexpr std::size_t kInventorySlotCount = 24;
    constexpr std::size_t kHotbarSlotCount = 10;

    struct Inventory
    {
        std::array<ItemStack, kInventorySlotCount> Slots{};

        [[nodiscard]] bool AddItem(const ItemDatabase& items, ItemStack incoming);
        [[nodiscard]] ItemStack RemoveFromSlot(std::size_t index, std::uint16_t count);
        [[nodiscard]] const ItemStack* GetSlot(std::size_t index) const;
        [[nodiscard]] ItemStack* GetSlot(std::size_t index);
    };
}
