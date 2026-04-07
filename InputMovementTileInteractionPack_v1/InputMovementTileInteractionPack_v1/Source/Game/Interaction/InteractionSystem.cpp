#include "Game/Interaction/InteractionSystem.h"

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

        FTile tile = map.GetTile(coord);
        switch (tile.Type)
        {
            case ETileType::Tree:
                map.SetTile(coord, { ETileType::Stump, false, true });
                return L"Interact: chopped tree -> stump";
            case ETileType::Rock:
                map.SetTile(coord, { ETileType::Dirt, false, true });
                return L"Interact: mined rock -> dirt";
            case ETileType::Dirt:
                map.SetTile(coord, { ETileType::TilledDirt, false, true });
                return L"Interact: tilled dirt";
            case ETileType::Grass:
                return L"Interact: inspected grass";
            case ETileType::Water:
                return L"Interact: water is not usable yet";
            case ETileType::Stump:
                map.SetTile(coord, { ETileType::Dirt, false, true });
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
