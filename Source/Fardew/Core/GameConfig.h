#pragma once

#include "Types.h"

namespace atlas
{
    struct GameConfig
    {
        s32 windowWidth = 1600;
        s32 windowHeight = 900;
        bool startInFullscreen = false;
        bool vsyncEnabled = true;
        f32 fixedTimeStepSeconds = 1.0f / 60.0f;
        s32 maxPlayers = 2;
    };
}
