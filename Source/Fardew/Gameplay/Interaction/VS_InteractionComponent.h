#pragma once

#include "Core/VS_Types.h"
#include "Gameplay/Interaction/VS_InteractionTypes.h"

struct InteractionComponent
{
    EntityId owner = InvalidEntity;
    InteractionType type = InteractionType::None;
    bool requiresExclusiveUse = true;
    bool locked = false;
    int lockedByPlayer = -1;
};
