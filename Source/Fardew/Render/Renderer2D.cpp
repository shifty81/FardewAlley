#include "Renderer2D.h"
#include "../Gameplay/Players/SplitScreen_PlayerState.h"
#include "../Gameplay/Farming/VS_FarmingSystem.h"
#include "../World/Tilemap/TilemapTypes.h"
#include "../World/Tilemap/CollisionGrid.h"
#include <algorithm>

namespace atlas
{
    // ---------------------------------------------------------------------------
    // Palette
    // ---------------------------------------------------------------------------
    namespace
    {
        struct RGB { Uint8 r, g, b; };

        constexpr RGB kColorBackground  = {  18,  18,  28 };
        constexpr RGB kColorGrass       = {  72, 112,  56 };
        constexpr RGB kColorGrassLight  = {  82, 126,  64 };   // checker variant
        constexpr RGB kColorWall        = {  44,  44,  44 };
        constexpr RGB kColorDirt        = { 140, 105,  50 };
        constexpr RGB kColorWetDirt     = {  90,  68,  32 };
        constexpr RGB kColorCrop        = {  50, 160,  50 };
        constexpr RGB kColorCropReady   = { 220, 180,  40 };
        constexpr RGB kColorPlayer0     = {  68, 136, 255 };   // blue
        constexpr RGB kColorPlayer1     = { 255,  80,  80 };   // red
        constexpr RGB kColorDivider     = { 200, 200, 200 };
    }

    // ---------------------------------------------------------------------------
    // Init / context
    // ---------------------------------------------------------------------------
    void Renderer2D::Init(SDL_Renderer* renderer, SDL_Window* window)
    {
        m_sdl    = renderer;
        m_window = window;
    }

    void Renderer2D::SetWorldContext(const TilemapData*   map,
                                     const CollisionGrid* collision,
                                     const FarmingSystem* farming,
                                     const PlayerState*   players,
                                     int                  playerCount)
    {
        m_tilemap     = map;
        m_collision   = collision;
        m_farming     = farming;
        m_players     = players;
        m_playerCount = playerCount;
    }

    // ---------------------------------------------------------------------------
    // Helper
    // ---------------------------------------------------------------------------
    void Renderer2D::FillRect(int sx, int sy, int sw, int sh, Uint8 r, Uint8 g, Uint8 b)
    {
        SDL_SetRenderDrawColor(m_sdl, r, g, b, 255);
        SDL_Rect rect{ sx, sy, sw, sh };
        SDL_RenderFillRect(m_sdl, &rect);
    }

    // ---------------------------------------------------------------------------
    // Frame lifecycle
    // ---------------------------------------------------------------------------
    void Renderer2D::BeginFrame()
    {
        if (!m_sdl) return;
        SDL_RenderSetViewport(m_sdl, nullptr);
        SDL_SetRenderDrawColor(m_sdl,
            kColorBackground.r, kColorBackground.g, kColorBackground.b, 255);
        SDL_RenderClear(m_sdl);
    }

    void Renderer2D::BeginViewport(const ViewportContext& viewport, const Camera2D& camera)
    {
        m_viewport = viewport;
        m_camera   = camera;

        if (!m_sdl) return;
        SDL_Rect sdlRect{
            viewport.viewportRect.x,
            viewport.viewportRect.y,
            viewport.viewportRect.w,
            viewport.viewportRect.h
        };
        SDL_RenderSetViewport(m_sdl, &sdlRect);
    }

    // ---------------------------------------------------------------------------
    // World rendering (called once per active player viewport)
    // ---------------------------------------------------------------------------
    void Renderer2D::RenderWorld(int /*playerIndex*/)
    {
        if (!m_sdl || !m_tilemap || !m_collision) return;

        const int tileSize   = m_tilemap->tileSize;  // 16 world units per tile
        const float zoom     = m_camera.zoom > 0.0f ? m_camera.zoom : 1.0f;
        const float tileDisp = tileSize * zoom;       // on-screen pixels per tile

        const int vw = m_viewport.viewportRect.w;
        const int vh = m_viewport.viewportRect.h;
        const float camX = m_camera.position.x;
        const float camY = m_camera.position.y;

        // Determine visible tile range.
        const float halfW = (vw * 0.5f) / zoom;
        const float halfH = (vh * 0.5f) / zoom;

        const int startTX = std::max(0, static_cast<int>((camX - halfW) / tileSize) - 1);
        const int startTY = std::max(0, static_cast<int>((camY - halfH) / tileSize) - 1);
        const int endTX   = std::min(m_tilemap->width  - 1,
                                     static_cast<int>((camX + halfW) / tileSize) + 1);
        const int endTY   = std::min(m_tilemap->height - 1,
                                     static_cast<int>((camY + halfH) / tileSize) + 1);

        // Draw tiles.
        for (int ty = startTY; ty <= endTY; ++ty)
        {
            for (int tx = startTX; tx <= endTX; ++tx)
            {
                const float worldX = static_cast<float>(tx * tileSize);
                const float worldY = static_cast<float>(ty * tileSize);

                const int sx = static_cast<int>((worldX - camX) * zoom + vw * 0.5f);
                const int sy = static_cast<int>((worldY - camY) * zoom + vh * 0.5f);
                const int sw = static_cast<int>(tileDisp) + 1; // +1 avoids hairline gaps
                const int sh = static_cast<int>(tileDisp) + 1;

                // Choose colour based on world state.
                RGB col = kColorGrass;

                if (m_collision->IsBlocked(tx, ty))
                {
                    col = kColorWall;
                }
                else
                {
                    // Checkerboard grass for visual interest.
                    if ((tx + ty) % 2 == 0) col = kColorGrassLight;

                    // Farming overlay (takes precedence over grass).
                    if (m_farming)
                    {
                        const FarmingTileState* ft = m_farming->TryGet(tx, ty);
                        if (ft && ft->soil == SoilState::Tilled)
                        {
                            col = ft->wateredToday ? kColorWetDirt : kColorDirt;
                        }
                    }
                }

                FillRect(sx, sy, sw, sh, col.r, col.g, col.b);

                // Crop indicator drawn on top of soil.
                if (m_farming)
                {
                    const FarmingTileState* ft = m_farming->TryGet(tx, ty);
                    if (ft && ft->hasCrop)
                    {
                        const RGB cropCol = ft->harvestReady ? kColorCropReady : kColorCrop;
                        const int pad = static_cast<int>(tileDisp * 0.2f);
                        FillRect(sx + pad, sy + pad,
                                 sw - pad * 2, sh - pad * 2,
                                 cropCol.r, cropCol.g, cropCol.b);
                    }
                }
            }
        }

        // Draw players.
        if (m_players)
        {
            for (int i = 0; i < m_playerCount; ++i)
            {
                const PlayerState& player = m_players[i];
                if (!player.isActive) continue;

                const float sx = (player.position.x - camX) * zoom + vw * 0.5f;
                const float sy = (player.position.y - camY) * zoom + vh * 0.5f;
                const int size = std::max(4, static_cast<int>(tileDisp * 0.75f));

                const RGB col = (i == 0) ? kColorPlayer0 : kColorPlayer1;
                FillRect(static_cast<int>(sx) - size / 2,
                         static_cast<int>(sy) - size / 2,
                         size, size,
                         col.r, col.g, col.b);

                // Direction indicator — small darker square on the facing edge.
                const int dotSize = std::max(2, size / 4);
                int dotX = static_cast<int>(sx) - dotSize / 2;
                int dotY = static_cast<int>(sy) - dotSize / 2;
                switch (player.facing)
                {
                    case Direction::Up:    dotY = static_cast<int>(sy) - size / 2; break;
                    case Direction::Down:  dotY = static_cast<int>(sy) + size / 2 - dotSize; break;
                    case Direction::Left:  dotX = static_cast<int>(sx) - size / 2; break;
                    case Direction::Right: dotX = static_cast<int>(sx) + size / 2 - dotSize; break;
                }
                FillRect(dotX, dotY, dotSize, dotSize, 255, 255, 255);
            }
        }
    }

    void Renderer2D::EndViewport()
    {
        if (m_sdl) SDL_RenderSetViewport(m_sdl, nullptr);
    }

    void Renderer2D::RenderGlobalOverlay(int activePlayerCount)
    {
        if (!m_sdl) return;

        SDL_RenderSetViewport(m_sdl, nullptr);

        if (activePlayerCount >= 2)
        {
            int winW = 0, winH = 0;
            SDL_GetWindowSize(m_window, &winW, &winH);
            const int midX = winW / 2;
            SDL_SetRenderDrawColor(m_sdl,
                kColorDivider.r, kColorDivider.g, kColorDivider.b, 255);
            SDL_RenderDrawLine(m_sdl, midX, 0, midX, winH);
        }
    }

    void Renderer2D::EndFrame()
    {
        if (m_sdl) SDL_RenderPresent(m_sdl);
    }

} // namespace atlas
