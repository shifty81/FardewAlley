#pragma once

#include <cstdint>
#include "Tools/ToolTypes.h"

namespace Game
{
    struct FToolData
    {
        EToolType Type = EToolType::None;
        const wchar_t* DisplayName = L"None";
        ETileActionAffinity Affinity = ETileActionAffinity::None;
        int32_t Power = 1;
        float RangeTiles = 1.0f;
        int32_t StaminaCost = 1;
        bool bConsumesWaterReserve = false;
    };
}
