#include "UIManager.h"

namespace atlas
{
    void UIManager::Initialize()
    {
    }

    PauseScope UIManager::HandleInput(int, PlayerInputContext& input, HUDContext& hud)
    {
        if (input.current.inventoryPressed)
        {
            hud.inventoryOpen = !hud.inventoryOpen;
            input.mode = hud.inventoryOpen ? InputMode::UI : InputMode::Gameplay;
            return PauseScope::LocalOnly;
        }

        if (input.current.menuPressed)
        {
            hud.localPauseOpen = !hud.localPauseOpen;
            input.mode = hud.localPauseOpen ? InputMode::Menu : InputMode::Gameplay;
            return PauseScope::Global;
        }

        return PauseScope::None;
    }

    void UIManager::RenderHUD(int) const
    {
        // TODO: player health, stamina, hotbar, prompt, local menus.
    }
}
