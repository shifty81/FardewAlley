#include "Gameplay/Inventory/VS_Inventory.h"

Inventory::Inventory(int slotCount)
    : m_slots(static_cast<size_t>(slotCount))
{
}

bool Inventory::Add(ItemType type, int count)
{
    for (auto& slot : m_slots)
    {
        if (slot.type == type && slot.count > 0)
        {
            slot.count += count;
            return true;
        }
    }
    for (auto& slot : m_slots)
    {
        if (slot.type == ItemType::None || slot.count <= 0)
        {
            slot.type = type;
            slot.count = count;
            return true;
        }
    }
    return false;
}

bool Inventory::Remove(ItemType type, int count)
{
    for (auto& slot : m_slots)
    {
        if (slot.type == type && slot.count >= count)
        {
            slot.count -= count;
            if (slot.count == 0)
                slot.type = ItemType::None;
            return true;
        }
    }
    return false;
}

int Inventory::Count(ItemType type) const
{
    int total = 0;
    for (const auto& slot : m_slots)
    {
        if (slot.type == type)
            total += slot.count;
    }
    return total;
}
