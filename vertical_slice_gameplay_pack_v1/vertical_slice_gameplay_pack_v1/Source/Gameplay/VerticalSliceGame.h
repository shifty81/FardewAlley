#pragma once

#include "Gameplay/GameplayWorld.h"
#include "Gameplay/Players/PlayerState.h"
#include "Gameplay/Inventory/Inventory.h"
#include "Render/Renderer2D.h"
#include "UI/HUDRenderer.h"
#include <array>

class VerticalSliceGame
{
public:
    bool Initialize();
    void Update(float deltaSeconds);
    void Render();
    void AdvanceToNextDay();

private:
    GameplayWorld m_world;
    std::array<PlayerState, 2> m_players{};
    std::array<Inventory, 2> m_inventories{ Inventory(24), Inventory(24) };
    std::array<ViewportContext, 2> m_viewports{};
    Renderer2D m_renderer;
    HUDRenderer m_hud;
};
