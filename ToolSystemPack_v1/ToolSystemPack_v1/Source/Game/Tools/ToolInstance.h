#pragma once

#include <cstdint>
#include "Game/Tools/ToolTypes.h"

namespace Game
{
    struct FToolInstance
    {
        EToolType Type = EToolType::None;
        int32_t UpgradeLevel = 0;
        int32_t DurabilityCurrent = -1;
        int32_t DurabilityMax = -1;
        int32_t WaterCurrent = 0;
        int32_t WaterMax = 0;
    };
}
