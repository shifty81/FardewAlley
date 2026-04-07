#pragma once

#include "../Core/MathTypes.h"

namespace atlas
{
    struct ViewportContext
    {
        int playerIndex = -1;
        IntRect viewportRect{};
        IntRect safeAreaRect{};
    };
}
