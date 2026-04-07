#pragma once

#include "Game/Movement/MovementComponent.h"
#include "Game/World/TileMap.h"

namespace Game
{
    class FMovementSystem
    {
    public:
        explicit FMovementSystem(const FTileMap& inTileMap)
            : TileMap(inTileMap)
        {
        }

        void Update(float deltaTime, FGridPosition& pos, FMovementComponent& move, bool bSprint);
        bool TryMove(FGridPosition& pos, FMovementComponent& move, FFacingComponent& facing, const FTileCoord& dir);

    private:
        bool IsTileBlocked(const FTileCoord& tile) const;
        static FVector2 TileToWorld(const FTileCoord& tile);

        const FTileMap& TileMap;
    };
}
