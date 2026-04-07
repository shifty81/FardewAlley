#include "Gameplay/Interaction/ChestSystem.h"
#include "Gameplay/Interaction/InteractionSystem.h"

bool ChestSystem::TryOpen(ChestState& chest, int playerIndex, std::string& outReason)
{
    InteractionSystem locks;
    if (!locks.TryAcquireLock(chest.interaction, playerIndex))
    {
        outReason = "Chest in use";
        return false;
    }

    outReason.clear();
    return true;
}

void ChestSystem::Close(ChestState& chest, int playerIndex)
{
    InteractionSystem locks;
    locks.ReleaseLock(chest.interaction, playerIndex);
}
