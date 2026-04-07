#include "GameApp.h"
#include <SDL2/SDL.h>

int main()
{
    atlas::GameConfig config{};
    atlas::GameApp app{};

    if (!app.Initialize(config))
    {
        return 1;
    }

    Uint32 lastTick = SDL_GetTicks();

    while (!app.ShouldQuit())
    {
        const Uint32 now = SDL_GetTicks();
        float dt = static_cast<float>(now - lastTick) / 1000.0f;
        lastTick = now;

        // Cap delta time so a stall (e.g. window move) doesn't cause a large jump.
        if (dt > 0.1f) dt = 0.1f;

        app.RunFrame(dt);
    }

    return 0;
}
