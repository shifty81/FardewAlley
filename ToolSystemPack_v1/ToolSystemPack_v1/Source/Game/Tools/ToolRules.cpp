#include "Game/Tools/ToolRules.h"

namespace Game
{
    bool FToolRules::CanApplyTool(const FToolData& tool, const FTileState& tile)
    {
        switch (tool.Type)
        {
            case EToolType::Axe:
                return tile.bHasTree;
            case EToolType::Pickaxe:
                return tile.bHasRock;
            case EToolType::Hoe:
                return !tile.bBlocked
                    && !tile.bHasTree
                    && !tile.bHasRock
                    && tile.BaseType != ETileType::Water
                    && tile.GroundState != EGroundState::Tilled
                    && tile.GroundState != EGroundState::Watered;
            case EToolType::WateringCan:
                return tile.GroundState == EGroundState::Tilled;
            default:
                return false;
        }
    }

    FActionResult FToolRules::ApplyTool(const FToolData& tool, FToolInstance& instance, FTileState& tile)
    {
        FActionResult result {};

        switch (tool.Type)
        {
            case EToolType::Axe:
            {
                if (!tile.bHasTree)
                {
                    result.Type = EActionResultType::InvalidTarget;
                    return result;
                }

                tile.bHasTree = false;
                tile.bBlocked = false;
                result.Type = EActionResultType::Success;
                result.bChangedWorld = true;
                result.bConsumeTurn = true;
                result.bConsumeStamina = true;
                return result;
            }

            case EToolType::Pickaxe:
            {
                if (!tile.bHasRock)
                {
                    result.Type = EActionResultType::InvalidTarget;
                    return result;
                }

                tile.bHasRock = false;
                tile.bBlocked = false;
                result.Type = EActionResultType::Success;
                result.bChangedWorld = true;
                result.bConsumeTurn = true;
                result.bConsumeStamina = true;
                return result;
            }

            case EToolType::Hoe:
            {
                if (!CanApplyTool(tool, tile))
                {
                    result.Type = EActionResultType::InvalidTarget;
                    return result;
                }

                tile.GroundState = EGroundState::Tilled;
                result.Type = EActionResultType::Success;
                result.bChangedWorld = true;
                result.bConsumeTurn = true;
                result.bConsumeStamina = true;
                return result;
            }

            case EToolType::WateringCan:
            {
                if (instance.WaterCurrent <= 0)
                {
                    result.Type = EActionResultType::NotEnoughResource;
                    return result;
                }
                if (tile.GroundState != EGroundState::Tilled)
                {
                    result.Type = EActionResultType::InvalidTarget;
                    return result;
                }

                tile.GroundState = EGroundState::Watered;
                instance.WaterCurrent -= 1;
                result.Type = EActionResultType::Success;
                result.bChangedWorld = true;
                result.bConsumeTurn = true;
                result.bConsumeStamina = true;
                return result;
            }

            default:
                result.Type = EActionResultType::NoToolEquipped;
                return result;
        }
    }
}
