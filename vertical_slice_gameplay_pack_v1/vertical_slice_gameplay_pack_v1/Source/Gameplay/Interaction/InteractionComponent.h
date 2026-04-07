#pragma once

#include "Core/Types.h"
#include "Gameplay/Interaction/InteractionTypes.h"

struct InteractionComponent
{
    EntityId owner = InvalidEntity;
    InteractionType type = InteractionType::None;
    bool requiresExclusiveUse = true;
    bool locked = false;
    int lockedByPlayer = -1;
};
