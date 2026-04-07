#pragma once

#include "../Core/FardewTypes.h"

namespace Fardew
{
    enum TileFlags : std::uint32_t
    {
        TileFlag_None = 0,
        TileFlag_Blocked = 1 << 0,
        TileFlag_Waterable = 1 << 1,
        TileFlag_Tillable = 1 << 2,
        TileFlag_Plantable = 1 << 3,
        TileFlag_Buildable = 1 << 4
    };

    struct TileState
    {
        TerrainType Terrain = TerrainType::Grass;
        std::uint32_t Flags = TileFlag_None;
        std::uint8_t Moisture = 0;
        EntityId CropInstanceId = 0;
        EntityId PlaceableInstanceId = 0;

        [[nodiscard]] bool HasCrop() const noexcept { return CropInstanceId != 0; }
        [[nodiscard]] bool HasPlaceable() const noexcept { return PlaceableInstanceId != 0; }
        [[nodiscard]] bool IsBlocked() const noexcept { return (Flags & TileFlag_Blocked) != 0; }
    };
}
