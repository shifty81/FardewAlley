#pragma once

#include <string>
#include "Gameplay/Interaction/IMT_InteractionComponent.h"
#include "Gameplay/Interaction/IMT_InteractionTypes.h"
#include "Movement/MovementComponent.h"
#include "Movement/GridPosition.h"
#include "World/TileMap/TileMap.h"

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
