#pragma once

#include "Game/Interaction/ActionContext.h"
#include "Game/Interaction/ActionResult.h"
#include "Game/Tools/ToolComponent.h"
#include "Game/Tools/ToolRegistry.h"
#include "Game/World/TileMap.h"

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
