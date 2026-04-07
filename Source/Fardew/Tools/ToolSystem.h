#pragma once

#include "Tools/ActionContext.h"
#include "Tools/ActionResult.h"
#include "Tools/ToolComponent.h"
#include "Tools/ToolRegistry.h"
#include "World/TileMap/TileMap.h"

namespace Game
{
    class FToolSystem
    {
    public:
        FActionResult UseEquippedTool(FToolComponent& toolComp, const FActionContext& context, FTileMap& map);
        const FToolData* GetToolData(EToolType type) const;

    private:
        bool IsInRange(const FActionContext& context, float rangeTiles) const;
    };
}
