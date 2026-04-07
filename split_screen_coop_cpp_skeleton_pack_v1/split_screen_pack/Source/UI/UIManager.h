#pragma once

#include "HUDContext.h"
#include "../Core/GameEnums.h"
#include "../Input/PlayerInputContext.h"

namespace atlas
{
    class UIManager
    {
    public:
        void Initialize();
        PauseScope HandleInput(int playerIndex, PlayerInputContext& input, HUDContext& hud);
        void RenderHUD(int playerIndex) const;

    private:
        // TODO: widget tree, focus routing, inventory widgets, dialogue widgets, prompt overlays.
    };
}
