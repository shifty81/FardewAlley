#include "UI/HUDRenderer.h"
#include <iostream>

void HUDRenderer::RenderPlayerHUD(const ViewportContext& viewport, const PlayerState& player, const Inventory& inventory) const
{
    (void)inventory;
    std::cout << "HUD P" << player.playerIndex + 1
              << " viewport=(" << viewport.x << "," << viewport.y << "," << viewport.width << "," << viewport.height << ") "
              << "HP=" << player.health << "/" << player.maxHealth
              << " ST=" << player.stamina << "/" << player.maxStamina
              << " Money=" << player.money << "\n";
}

void HUDRenderer::RenderInteractionPrompt(const ViewportContext& viewport, const std::string& text) const
{
    std::cout << "Prompt viewport=(" << viewport.x << "," << viewport.y << ") " << text << "\n";
}

void HUDRenderer::RenderGlobalClock(int day, int hour, int minute) const
{
    std::cout << "Day " << day << " " << hour << ":" << minute << "\n";
}
