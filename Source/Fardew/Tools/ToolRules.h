#pragma once

#include "Tools/ActionResult.h"
#include "Tools/ToolData.h"
#include "Tools/ToolInstance.h"
#include "World/TileMap/TileState.h"

namespace Game
{
    class FToolRules
    {
    public:
        static bool CanApplyTool(const FToolData& tool, const FTileState& tile);
        static FActionResult ApplyTool(const FToolData& tool, FToolInstance& instance, FTileState& tile);
    };
}
