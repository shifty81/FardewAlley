#pragma once

#include "Movement/GridPosition.h"
#include "Movement/MovementComponent.h"

namespace Game
{
    enum class EToolUseType
    {
        None,
        PrimaryAction
    };

    struct FActionContext
    {
        FTileCoord ActorTile {};
        FTileCoord TargetTile {};
        EFacingDirection Facing = EFacingDirection::Down;
        EToolUseType UseType = EToolUseType::PrimaryAction;
    };
}
