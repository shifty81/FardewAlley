#pragma once

#include "Gameplay/Interaction/VS_InteractionComponent.h"
#include <vector>

class InteractionSystem
{
public:
    bool TryAcquireLock(InteractionComponent& component, int playerIndex);
    void ReleaseLock(InteractionComponent& component, int playerIndex);
    bool IsBusyFor(const InteractionComponent& component, int playerIndex) const;
};
