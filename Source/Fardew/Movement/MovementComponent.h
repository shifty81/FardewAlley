#pragma once

#include "Movement/GridPosition.h"

namespace Game
{
    struct FMovementComponent
    {
        float MoveSpeedTilesPerSecond = 4.0f;
        float SprintMultiplier = 1.75f;
        bool bIsMoving = false;
        FVector2 Velocity {};
        FTileCoord StartTile {};
        FTileCoord TargetTile {};
    };

    enum class EFacingDirection
    {
        Up,
        Down,
        Left,
        Right
    };

    struct FFacingComponent
    {
        EFacingDirection Direction = EFacingDirection::Down;
    };
}
