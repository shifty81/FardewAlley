#include "Game/Movement/MovementSystem.h"
#include <cmath>

namespace Game
{
    namespace
    {
        constexpr float TileSize = 1.0f;

        float MoveToward(float current, float target, float maxDelta)
        {
            const float delta = target - current;
            if (std::fabs(delta) <= maxDelta)
            {
                return target;
            }
            return current + (delta > 0.0f ? maxDelta : -maxDelta);
        }
    }

    FVector2 FMovementSystem::TileToWorld(const FTileCoord& tile)
    {
        return FVector2 {
            static_cast<float>(tile.X) * TileSize,
            static_cast<float>(tile.Y) * TileSize
        };
    }

    bool FMovementSystem::IsTileBlocked(const FTileCoord& tile) const
    {
        return TileMap.IsBlocked(tile);
    }

    bool FMovementSystem::TryMove(FGridPosition& pos, FMovementComponent& move, FFacingComponent& facing, const FTileCoord& dir)
    {
        if (move.bIsMoving)
        {
            return false;
        }

        if (dir.X == 0 && dir.Y == 0)
        {
            return false;
        }

        if (dir.X > 0) facing.Direction = EFacingDirection::Right;
        else if (dir.X < 0) facing.Direction = EFacingDirection::Left;
        else if (dir.Y > 0) facing.Direction = EFacingDirection::Down;
        else if (dir.Y < 0) facing.Direction = EFacingDirection::Up;

        const FTileCoord nextTile { pos.Tile.X + dir.X, pos.Tile.Y + dir.Y };
        if (IsTileBlocked(nextTile))
        {
            return false;
        }

        move.bIsMoving = true;
        move.StartTile = pos.Tile;
        move.TargetTile = nextTile;
        return true;
    }

    void FMovementSystem::Update(float deltaTime, FGridPosition& pos, FMovementComponent& move, bool bSprint)
    {
        if (!move.bIsMoving)
        {
            pos.World = TileToWorld(pos.Tile);
            return;
        }

        const FVector2 target = TileToWorld(move.TargetTile);
        const float speed = move.MoveSpeedTilesPerSecond * (bSprint ? move.SprintMultiplier : 1.0f);
        const float step = speed * deltaTime;

        pos.World.X = MoveToward(pos.World.X, target.X, step);
        pos.World.Y = MoveToward(pos.World.Y, target.Y, step);

        if (std::fabs(pos.World.X - target.X) < 0.0001f && std::fabs(pos.World.Y - target.Y) < 0.0001f)
        {
            pos.World = target;
            pos.Tile = move.TargetTile;
            move.bIsMoving = false;
        }
    }
}
