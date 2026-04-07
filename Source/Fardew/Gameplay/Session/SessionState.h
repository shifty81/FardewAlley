#pragma once

#include "../../Core/GameEnums.h"

namespace atlas
{
    struct SessionState
    {
        SessionMode mode = SessionMode::SinglePlayer;
        SplitMode splitMode = SplitMode::None;
        bool globalPauseActive = false;
        bool sleepVoteActive = false;
        bool playerReadyForSleep[2] = { false, false };
        int activePlayerCount = 1;
    };
}
