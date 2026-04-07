#include "GameApp.h"

int main()
{
    atlas::GameConfig config{};
    atlas::GameApp app{};

    if (!app.Initialize(config))
    {
        return 1;
    }

    // TODO: replace with real platform loop and fixed timestep.
    for (;;)
    {
        app.RunFrame(config.fixedTimeStepSeconds);
    }

    return 0;
}
