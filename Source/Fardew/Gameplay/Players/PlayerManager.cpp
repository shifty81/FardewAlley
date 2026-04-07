#include "PlayerManager.h"

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
            player.velocity.x = in.moveX * moveSpeed;
            player.velocity.y = in.moveY * moveSpeed;

            player.position.x += player.velocity.x * dt;
            player.position.y += player.velocity.y * dt;

            if (player.velocity.x != 0.0f || player.velocity.y != 0.0f)
            {
                player.animState = PlayerAnimState::Walk;
            }
            else
            {
                player.animState = PlayerAnimState::Idle;
            }

            // TODO: collision, tool use, combat, interaction targeting, animation facing.
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
