#include "PlayerState.h"

namespace Fardew
{
    ItemStack PlayerState::GetSelectedItem() const
    {
        if (SelectedHotbarSlot >= kHotbarSlotCount)
        {
            return {};
        }
        return Bag.Slots[SelectedHotbarSlot];
    }
}
