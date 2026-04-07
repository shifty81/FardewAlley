#include "Tools/ToolSystem.h"
#include <cstdlib>
#include "Tools/ToolRules.h"

namespace Game
{
    const FToolData* FToolSystem::GetToolData(EToolType type) const
    {
        const FToolData& data = FToolRegistry::Get(type);
        return data.Type == EToolType::None ? nullptr : &data;
    }

    bool FToolSystem::IsInRange(const FActionContext& context, float rangeTiles) const
    {
        const int dx = std::abs(context.TargetTile.X - context.ActorTile.X);
        const int dy = std::abs(context.TargetTile.Y - context.ActorTile.Y);
        return (dx + dy) <= static_cast<int>(rangeTiles);
    }

    FActionResult FToolSystem::UseEquippedTool(FToolComponent& toolComp, const FActionContext& context, FTileMap& map)
    {
        const FToolData* toolData = GetToolData(toolComp.Equipped.Type);
        if (toolData == nullptr)
        {
            return { EActionResultType::NoToolEquipped, false, false, false };
        }

        if (!map.IsInBounds(context.TargetTile))
        {
            return { EActionResultType::InvalidTarget, false, false, false };
        }

        if (!IsInRange(context, toolData->RangeTiles))
        {
            return { EActionResultType::OutOfRange, false, false, false };
        }

        FTileState& tile = map.GetTileMutable(context.TargetTile);
        if (!FToolRules::CanApplyTool(*toolData, tile))
        {
            if (toolData->Type == EToolType::WateringCan && toolComp.Equipped.WaterCurrent <= 0)
            {
                return { EActionResultType::NotEnoughResource, false, false, false };
            }
            return { EActionResultType::InvalidTarget, false, false, false };
        }

        return FToolRules::ApplyTool(*toolData, toolComp.Equipped, tile);
    }
}
