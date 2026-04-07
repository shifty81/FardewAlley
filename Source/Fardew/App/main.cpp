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

    // Maximum delta-time allowed in a single frame (caps physics/logic on stalls
    // such as window moves or debugger pauses).
    constexpr float kMaxDeltaTimeSeconds = 0.1f;

    Uint32 lastTick = SDL_GetTicks();

    while (!app.ShouldQuit())
    {
        const Uint32 now = SDL_GetTicks();
        float dt = static_cast<float>(now - lastTick) / 1000.0f;
        lastTick = now;

        if (dt > kMaxDeltaTimeSeconds) dt = kMaxDeltaTimeSeconds;

        app.RunFrame(dt);
    }

    return 0;
}
