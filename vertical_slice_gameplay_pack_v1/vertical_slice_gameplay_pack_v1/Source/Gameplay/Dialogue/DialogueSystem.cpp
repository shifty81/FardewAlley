#include "Gameplay/Dialogue/DialogueSystem.h"

bool DialogueSystem::TryBeginNpcDialogue(InteractionComponent& npcInteraction, int playerIndex, std::string& outMessage)
{
    InteractionSystem lockSystem;
    if (!lockSystem.TryAcquireLock(npcInteraction, playerIndex))
    {
        outMessage = "Busy";
        return false;
    }

    outMessage = "Hello there.";
    return true;
}

void DialogueSystem::EndNpcDialogue(InteractionComponent& npcInteraction, int playerIndex)
{
    InteractionSystem lockSystem;
    lockSystem.ReleaseLock(npcInteraction, playerIndex);
}
