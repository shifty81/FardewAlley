#pragma once

#include <cstdint>

namespace Game
{
    struct FVector2
    {
        float X = 0.0f;
        float Y = 0.0f;
    };

    struct FTileCoord
    {
        int32_t X = 0;
        int32_t Y = 0;

        bool operator==(const FTileCoord& other) const
        {
            return X == other.X && Y == other.Y;
        }
    };

    struct FGridPosition
    {
        FTileCoord Tile {};
        FVector2 World {};
    };
}
