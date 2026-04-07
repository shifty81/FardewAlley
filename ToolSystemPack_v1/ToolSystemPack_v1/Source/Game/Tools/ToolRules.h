#pragma once

#include "Game/Interaction/ActionResult.h"
#include "Game/Tools/ToolData.h"
#include "Game/Tools/ToolInstance.h"
#include "Game/World/TileState.h"

namespace Game
{
    class FToolRules
    {
    public:
        static bool CanApplyTool(const FToolData& tool, const FTileState& tile);
        static FActionResult ApplyTool(const FToolData& tool, FToolInstance& instance, FTileState& tile);
    };
}
