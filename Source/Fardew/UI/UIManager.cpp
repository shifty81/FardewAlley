#include "UIManager.h"
#include "../Gameplay/Players/SplitScreen_PlayerState.h"
#include <SDL2/SDL.h>
#include <algorithm>

namespace atlas
{
    void UIManager::Initialize()
    {
    }

    void UIManager::SetRenderContext(SDL_Renderer* renderer,
                                     const PlayerState* players,
                                     int playerCount)
    {
        m_sdl         = renderer;
        m_players     = players;
        m_playerCount = playerCount;
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

    // ---------------------------------------------------------------------------
    // Helpers
    // ---------------------------------------------------------------------------

    void UIManager::DrawBar(int x, int y, int w, int h,
                            int value, int maxValue,
                            unsigned char r, unsigned char g, unsigned char b) const
    {
        if (!m_sdl || maxValue <= 0) return;

        // Background (dark).
        SDL_SetRenderDrawColor(m_sdl, 20, 20, 20, 200);
        SDL_Rect bg{ x, y, w, h };
        SDL_RenderFillRect(m_sdl, &bg);

        // Filled portion.
        const int filled = static_cast<int>(
            (static_cast<long long>(std::clamp(value, 0, maxValue)) * w) / maxValue);
        if (filled > 0)
        {
            SDL_SetRenderDrawColor(m_sdl, r, g, b, 255);
            SDL_Rect fill{ x, y, filled, h };
            SDL_RenderFillRect(m_sdl, &fill);
        }
    }

    // ---------------------------------------------------------------------------
    // RenderHUD — draws health bar, stamina bar, and hotbar for one player.
    // The SDL viewport is already restricted to this player's screen area.
    // ---------------------------------------------------------------------------
    void UIManager::RenderHUD(int playerIndex, const ViewportContext& viewport) const
    {
        if (!m_sdl || !m_players) return;
        if (playerIndex < 0 || playerIndex >= m_playerCount) return;

        const PlayerState& player = m_players[playerIndex];
        if (!player.isActive) return;

        const int vw = viewport.viewportRect.w;
        const int vh = viewport.viewportRect.h;

        // --- Status bars (top-left corner) ---
        constexpr int kBarW = 120;
        constexpr int kBarH = 8;
        constexpr int kBarX = 8;
        constexpr int kBarPad = 3;

        // Health bar — red.
        DrawBar(kBarX, 8, kBarW, kBarH,
                player.health, player.maxHealth,
                200, 60, 60);

        // Stamina bar — yellow-green.
        DrawBar(kBarX, 8 + kBarH + kBarPad, kBarW, kBarH,
                player.stamina, player.maxStamina,
                180, 200, 50);

        // --- Hotbar (bottom-centre) ---
        constexpr int kSlotSize  = 36;
        constexpr int kSlotPad   = 4;
        const int totalW = PlayerState::kHotbarSize * (kSlotSize + kSlotPad) - kSlotPad;
        const int startX = (vw - totalW) / 2;
        const int startY = vh - kSlotSize - 10;

        for (int s = 0; s < PlayerState::kHotbarSize; ++s)
        {
            const int sx = startX + s * (kSlotSize + kSlotPad);
            const int sy = startY;

            const bool selected = (s == player.selectedHotbarSlot);

            // Slot background.
            SDL_SetRenderDrawColor(m_sdl, 30, 30, 30, 210);
            SDL_Rect slotBg{ sx, sy, kSlotSize, kSlotSize };
            SDL_RenderFillRect(m_sdl, &slotBg);

            // Selection highlight.
            if (selected)
            {
                SDL_SetRenderDrawColor(m_sdl, 255, 220, 60, 255);
                SDL_RenderDrawRect(m_sdl, &slotBg);
            }
            else
            {
                SDL_SetRenderDrawColor(m_sdl, 90, 90, 90, 255);
                SDL_RenderDrawRect(m_sdl, &slotBg);
            }

            // Item colour block when slot is occupied.
            const HotbarSlot& slot = player.hotbar[s];
            if (slot.type != ItemType::None && slot.count > 0)
            {
                unsigned char ir = 180, ig = 180, ib = 180;
                switch (slot.type)
                {
                    case ItemType::Hoe:         ir = 180; ig = 120; ib =  60; break;
                    case ItemType::WateringCan: ir =  60; ig = 140; ib = 200; break;
                    case ItemType::SeedTurnip:  ir = 100; ig = 200; ib =  80; break;
                    case ItemType::Turnip:      ir = 220; ig = 180; ib =  40; break;
                    case ItemType::Wood:        ir = 160; ig = 110; ib =  50; break;
                    case ItemType::Stone:       ir = 140; ig = 140; ib = 140; break;
                    default: break;
                }
                constexpr int pad = 6;
                SDL_SetRenderDrawColor(m_sdl, ir, ig, ib, 255);
                SDL_Rect icon{ sx + pad, sy + pad,
                               kSlotSize - pad * 2, kSlotSize - pad * 2 };
                SDL_RenderFillRect(m_sdl, &icon);
            }
        }
    }
}
