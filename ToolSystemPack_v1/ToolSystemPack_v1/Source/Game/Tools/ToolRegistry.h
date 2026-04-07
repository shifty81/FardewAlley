#pragma once

#include "Game/Tools/ToolData.h"

namespace Game
{
    class FToolRegistry
    {
    public:
        static const FToolData& Get(EToolType type);
    };
}
