#pragma once

#include "Game/Movement/GridPosition.h"
#include "Game/Movement/MovementComponent.h"

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
