#pragma once

#include "Gameplay/Players/VS_PlayerState.h"
#include "Gameplay/Inventory/Inventory.h"
#include <string>

struct ViewportContext
{
    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;
};

class HUDRenderer
{
public:
    void RenderPlayerHUD(const ViewportContext& viewport, const PlayerState& player, const Inventory& inventory) const;
    void RenderInteractionPrompt(const ViewportContext& viewport, const std::string& text) const;
    void RenderGlobalClock(int day, int hour, int minute) const;
};
