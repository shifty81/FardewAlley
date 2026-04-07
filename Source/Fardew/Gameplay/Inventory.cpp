#include "Inventory.h"

namespace Fardew
{
    bool Inventory::AddItem(const ItemDatabase& items, ItemStack incoming)
    {
        if (incoming.IsEmpty())
        {
            return true;
        }

        const ItemDefinition* definition = items.Find(incoming.Id);
        if (definition == nullptr)
        {
            return false;
        }

        for (ItemStack& slot : Slots)
        {
            if (slot.Id == incoming.Id && slot.Count < definition->MaxStack)
            {
                const auto freeSpace = static_cast<std::uint16_t>(definition->MaxStack - slot.Count);
                const auto moved = static_cast<std::uint16_t>(incoming.Count > freeSpace ? freeSpace : incoming.Count);
                slot.Count = static_cast<std::uint16_t>(slot.Count + moved);
                incoming.Count = static_cast<std::uint16_t>(incoming.Count - moved);
                if (incoming.Count == 0)
                {
                    return true;
                }
            }
        }

        for (ItemStack& slot : Slots)
        {
            if (slot.IsEmpty())
            {
                slot = incoming;
                return true;
            }
        }

        return false;
    }

    ItemStack Inventory::RemoveFromSlot(std::size_t index, std::uint16_t count)
    {
        if (index >= Slots.size())
        {
            return {};
        }

        ItemStack& slot = Slots[index];
        if (slot.IsEmpty())
        {
            return {};
        }

        const std::uint16_t removedCount = count > slot.Count ? slot.Count : count;
        ItemStack removed{ slot.Id, removedCount };
        slot.Count = static_cast<std::uint16_t>(slot.Count - removedCount);
        if (slot.Count == 0)
        {
            slot.Id = 0;
        }
        return removed;
    }

    const ItemStack* Inventory::GetSlot(std::size_t index) const
    {
        return index < Slots.size() ? &Slots[index] : nullptr;
    }

    ItemStack* Inventory::GetSlot(std::size_t index)
    {
        return index < Slots.size() ? &Slots[index] : nullptr;
    }
}
