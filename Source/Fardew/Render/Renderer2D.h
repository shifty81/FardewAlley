#pragma once

#include <SDL2/SDL.h>
#include "Camera2D.h"
#include "ViewportContext.h"

// Forward-declared to keep VS-pack global-namespace type aliases out of this header.
class CollisionGrid;
struct TilemapData;
class FarmingSystem;
namespace atlas { struct PlayerState; }

namespace atlas
{
    class Renderer2D
    {
    public:
        /// Call once after SDL_Renderer is created.
        void Init(SDL_Renderer* renderer, SDL_Window* window);

        /// Supply const pointers to world state; pointers must remain valid for the
        /// lifetime of the renderer.
        void SetWorldContext(const TilemapData*   map,
                             const CollisionGrid* collision,
                             const FarmingSystem* farming,
                             const PlayerState*   players,
                             int                  playerCount);

        void BeginFrame();
        void BeginViewport(const ViewportContext& viewport, const Camera2D& camera);
        void RenderWorld(int playerIndex);
        void EndViewport();
        void RenderGlobalOverlay(int activePlayerCount);
        void EndFrame();

    private:
        void FillRect(int sx, int sy, int sw, int sh, Uint8 r, Uint8 g, Uint8 b);

        SDL_Renderer* m_sdl    = nullptr;
        SDL_Window*   m_window = nullptr;

        const TilemapData*   m_tilemap    = nullptr;
        const CollisionGrid* m_collision  = nullptr;
        const FarmingSystem* m_farming    = nullptr;
        const PlayerState*   m_players    = nullptr;
        int                  m_playerCount = 0;

        // Set per BeginViewport call; used in RenderWorld.
        ViewportContext m_viewport{};
        Camera2D        m_camera{};
    };
}
