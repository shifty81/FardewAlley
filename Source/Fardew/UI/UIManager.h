#pragma once

#include "HUDContext.h"
#include "../Core/GameEnums.h"
#include "../Input/PlayerInputContext.h"
#include "../Render/ViewportContext.h"

// SDL opaque type — avoid including SDL in every TU that includes UIManager.h.
struct SDL_Renderer;

namespace atlas
{
    struct PlayerState;

    class UIManager
    {
    public:
        void Initialize();

        /// Supply context needed for SDL2 HUD rendering.
        void SetRenderContext(SDL_Renderer* renderer,
                              const PlayerState* players,
                              int playerCount);

        PauseScope HandleInput(int playerIndex, PlayerInputContext& input, HUDContext& hud);
        void RenderHUD(int playerIndex, const ViewportContext& viewport) const;

    private:
        void DrawBar(int x, int y, int w, int h,
                     int value, int maxValue,
                     unsigned char r, unsigned char g, unsigned char b) const;

        SDL_Renderer*      m_sdl         = nullptr;
        const PlayerState* m_players     = nullptr;
        int                m_playerCount = 0;
    };
}
