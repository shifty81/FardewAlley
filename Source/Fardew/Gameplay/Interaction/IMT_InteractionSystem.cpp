#include "Gameplay/Interaction/IMT_InteractionSystem.h"

namespace Game
{
    FTileCoord FInteractionSystem::GetTargetTile(const FTileCoord& origin, EFacingDirection dir, int range) const
    {
        FTileCoord target = origin;
        switch (dir)
        {
            case EFacingDirection::Up:    target.Y -= range; break;
            case EFacingDirection::Down:  target.Y += range; break;
            case EFacingDirection::Left:  target.X -= range; break;
            case EFacingDirection::Right: target.X += range; break;
        }
        return target;
    }

    std::wstring FInteractionSystem::ExecuteInteraction(const FTileCoord& coord, FTileMap& map)
    {
        if (!map.IsInBounds(coord))
        {
            return L"Interact: out of bounds";
        }

        FTileState& tile = map.GetTileMutable(coord);
        switch (tile.BaseType)
        {
            case ETileType::Tree:
                tile = FTileState{ ETileType::Stump, EGroundState::None, false, false, false };
                return L"Interact: chopped tree -> stump";
            case ETileType::Rock:
                tile = FTileState{ ETileType::Dirt, EGroundState::None, false, false, false };
                return L"Interact: mined rock -> dirt";
            case ETileType::Dirt:
                tile = FTileState{ ETileType::TilledDirt, EGroundState::Tilled, false, false, false };
                return L"Interact: tilled dirt";
            case ETileType::Grass:
                return L"Interact: inspected grass";
            case ETileType::Water:
                return L"Interact: water is not usable yet";
            case ETileType::Stump:
                tile = FTileState{ ETileType::Dirt, EGroundState::None, false, false, false };
                return L"Interact: removed stump";
            default:
                return L"Interact: nothing happened";
        }
    }

    std::wstring FInteractionSystem::TryInteract(
        const FGridPosition& pos,
        const FFacingComponent& facing,
        const FInteractionComponent& interaction,
        FTileMap& map)
    {
        const FTileCoord target = GetTargetTile(pos.Tile, facing.Direction, interaction.RangeInTiles);
        return ExecuteInteraction(target, map);
    }
}
