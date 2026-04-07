#pragma once

#include "Gameplay/Interaction/InteractionComponent.h"
#include "Gameplay/Inventory/Inventory.h"
#include <string>

struct ChestState
{
    InteractionComponent interaction;
    Inventory inventory{24};
};

class ChestSystem
{
public:
    bool TryOpen(ChestState& chest, int playerIndex, std::string& outReason);
    void Close(ChestState& chest, int playerIndex);
};
