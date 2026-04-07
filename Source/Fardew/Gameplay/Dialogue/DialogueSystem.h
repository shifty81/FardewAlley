#pragma once

#include "Gameplay/Interaction/VS_InteractionSystem.h"
#include <string>

class DialogueSystem
{
public:
    bool TryBeginNpcDialogue(InteractionComponent& npcInteraction, int playerIndex, std::string& outMessage);
    void EndNpcDialogue(InteractionComponent& npcInteraction, int playerIndex);
};
