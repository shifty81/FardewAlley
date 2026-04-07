#include "Gameplay/Interaction/VS_InteractionSystem.h"

bool InteractionSystem::TryAcquireLock(InteractionComponent& component, int playerIndex)
{
    if (!component.requiresExclusiveUse)
        return true;

    if (!component.locked)
    {
        component.locked = true;
        component.lockedByPlayer = playerIndex;
        return true;
    }

    return component.lockedByPlayer == playerIndex;
}

void InteractionSystem::ReleaseLock(InteractionComponent& component, int playerIndex)
{
    if (component.locked && component.lockedByPlayer == playerIndex)
    {
        component.locked = false;
        component.lockedByPlayer = -1;
    }
}

bool InteractionSystem::IsBusyFor(const InteractionComponent& component, int playerIndex) const
{
    return component.locked && component.lockedByPlayer != playerIndex;
}
