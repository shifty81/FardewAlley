#pragma once

#include "../Core/GameEnums.h"
#include "InputSnapshot.h"

namespace atlas
{
    using InputDeviceId = int;

    struct PlayerInputContext
    {
        int playerIndex = -1;
        InputDeviceId deviceId = -1;
        InputMode mode = InputMode::Gameplay;
        InputSnapshot current;
        InputSnapshot previous;
    };
}
