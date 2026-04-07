#pragma once

#include "Gameplay/Inventory/ItemTypes.h"
#include <vector>

struct ItemStack
{
    ItemType type = ItemType::None;
    int count = 0;
};

class Inventory
{
public:
    explicit Inventory(int slotCount = 24);

    bool Add(ItemType type, int count);
    bool Remove(ItemType type, int count);
    int Count(ItemType type) const;

    const std::vector<ItemStack>& GetSlots() const { return m_slots; }

private:
    std::vector<ItemStack> m_slots;
};
