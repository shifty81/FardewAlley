#pragma once

#include "World/TileMap/TileTypes.h"

namespace Game
{
    struct FTileState
    {
        ETileType BaseType = ETileType::Empty;
        EGroundState GroundState = EGroundState::None;
        bool bBlocked = false;
        bool bHasTree = false;
        bool bHasRock = false;
    };
}
