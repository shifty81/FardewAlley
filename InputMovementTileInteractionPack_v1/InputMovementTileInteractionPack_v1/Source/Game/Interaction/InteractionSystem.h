#pragma once

#include <string>
#include "Game/Interaction/InteractionComponent.h"
#include "Game/Interaction/InteractionTypes.h"
#include "Game/Movement/MovementComponent.h"
#include "Game/Movement/GridPosition.h"
#include "Game/World/TileMap.h"

namespace Game
{
    class FInteractionSystem
    {
    public:
        std::wstring TryInteract(
            const FGridPosition& pos,
            const FFacingComponent& facing,
            const FInteractionComponent& interaction,
            FTileMap& map);

    private:
        FTileCoord GetTargetTile(const FTileCoord& origin, EFacingDirection dir, int range) const;
        std::wstring ExecuteInteraction(const FTileCoord& coord, FTileMap& map);
    };
}
