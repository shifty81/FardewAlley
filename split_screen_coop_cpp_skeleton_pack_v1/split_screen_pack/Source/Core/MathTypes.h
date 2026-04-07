#pragma once

#include "Types.h"

namespace atlas
{
    struct Vec2
    {
        f32 x = 0.0f;
        f32 y = 0.0f;
    };

    struct Int2
    {
        s32 x = 0;
        s32 y = 0;
    };

    struct Rect
    {
        f32 x = 0.0f;
        f32 y = 0.0f;
        f32 w = 0.0f;
        f32 h = 0.0f;
    };

    struct IntRect
    {
        s32 x = 0;
        s32 y = 0;
        s32 w = 0;
        s32 h = 0;
    };
}
