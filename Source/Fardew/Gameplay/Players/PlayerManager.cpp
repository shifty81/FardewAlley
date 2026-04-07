#include "PlayerManager.h"
#include "../../Gameplay/GameplayRules.h"
#include "../../World/Tilemap/CollisionGrid.h"

namespace atlas
{
    void PlayerManager::Initialize()
    {
        for (int i = 0; i < 2; ++i)
        {
            m_players[i].playerIndex = i;
        }
    }

    void PlayerManager::ActivatePlayer(int playerIndex, ZoneId zone, Vec2 spawnPosition)
    {
        PlayerState& player = m_players[playerIndex];
        player.isActive = true;
        player.zone = zone;
        player.position = spawnPosition;
        player.velocity = {};
        player.isTransitioning = false;
    }

    void PlayerManager::DeactivatePlayer(int playerIndex)
    {
        m_players[playerIndex].isActive = false;
    }

    void PlayerManager::SetCollisionGrid(const CollisionGrid* grid)
    {
        m_collisionGrid = grid;
    }

    void PlayerManager::UpdateGameplayInput(float dt, const PlayerInputContext inputs[2])
    {
        constexpr float moveSpeed = 90.0f;

        for (int i = 0; i < 2; ++i)
        {
            PlayerState& player = m_players[i];
            if (!player.isActive || player.isTransitioning)
            {
                continue;
            }

            const auto& in = inputs[i].current;
            const float vx = in.moveX * moveSpeed;
            const float vy = in.moveY * moveSpeed;

            const float tileSize = static_cast<float>(GameplayRules::TileSize);

            // Axis-separated collision so players can slide along walls.
            const float newX    = player.position.x + vx * dt;
            const int newTileX  = static_cast<int>(newX / tileSize);
            const int tileY     = static_cast<int>(player.position.y / tileSize);
            if (!m_collisionGrid || !m_collisionGrid->IsBlocked(newTileX, tileY))
            {
                player.position.x = newX;
            }

            const float newY    = player.position.y + vy * dt;
            const int tileX     = static_cast<int>(player.position.x / tileSize);
            const int newTileY  = static_cast<int>(newY / tileSize);
            if (!m_collisionGrid || !m_collisionGrid->IsBlocked(tileX, newTileY))
            {
                player.position.y = newY;
            }

            player.velocity.x = vx;
            player.velocity.y = vy;

            if (vx != 0.0f || vy != 0.0f)
            {
                player.animState = PlayerAnimState::Walk;
            }
            else
            {
                player.animState = PlayerAnimState::Idle;
            }

            // TODO: tool use, combat, interaction targeting, animation facing.
        }
    }

    void PlayerManager::ApplyZoneTransition(int playerIndex, const ZoneTransition& transition)
    {
        PlayerState& player = m_players[playerIndex];
        player.zone = transition.targetZone;
        player.position = transition.targetSpawnPosition;
        player.velocity = {};
        player.isTransitioning = false;
    }

    PlayerState& PlayerManager::GetPlayer(int playerIndex)
    {
        return m_players[playerIndex];
    }

    const PlayerState& PlayerManager::GetPlayer(int playerIndex) const
    {
        return m_players[playerIndex];
    }
}
