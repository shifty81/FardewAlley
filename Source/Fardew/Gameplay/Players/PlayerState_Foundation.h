#pragma once

#include "../Inventory.h"
#include "../../Core/FardewTypes.h"

namespace Fardew
{
    struct LocalViewportBinding
    {
        std::uint8_t LocalPlayerIndex = 0;
        std::uint8_t ControllerIndex = 0;
        bool IsHost = false;
    };

    struct PlayerState
    {
        PlayerId Id = 0;
        Int2 Tile{};
        Facing FacingDirection = Facing::Down;
        std::uint16_t Health = 100;
        std::uint16_t Stamina = 100;
        std::uint8_t SelectedHotbarSlot = 0;
        bool InventoryOpen = false;
        Inventory Bag{};
        LocalViewportBinding Viewport{};

        [[nodiscard]] ItemStack GetSelectedItem() const;
    };
}
