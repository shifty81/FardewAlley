#include "PlayerManager.h"
#include "../../Gameplay/GameplayRules.h"
#include "../../World/Tilemap/CollisionGrid.h"
#include "../../Gameplay/Farming/VS_FarmingSystem.h"
#include <cmath>
#include <algorithm>

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

    void PlayerManager::SetFarmingSystem(FarmingSystem* farming)
    {
        m_farming = farming;
    }

    // Compute the tile one step ahead in the player's facing direction.
    static void GetFacingTile(const PlayerState& player, int& outX, int& outY)
    {
        const float tileF = static_cast<float>(GameplayRules::TileSize);
        const int ptx = static_cast<int>(player.position.x / tileF);
        const int pty = static_cast<int>(player.position.y / tileF);
        int dx = 0, dy = 0;
        switch (player.facing)
        {
            case Direction::Up:    dy = -1; break;
            case Direction::Down:  dy =  1; break;
            case Direction::Left:  dx = -1; break;
            case Direction::Right: dx =  1; break;
        }
        outX = ptx + dx;
        outY = pty + dy;
    }

    // Days required for a turnip to reach harvest-ready state.
    static constexpr int kTurnipGrowthDays = 4;

    void PlayerManager::DispatchToolUse(PlayerState& player)
    {
        if (!m_farming) return;

        const HotbarSlot& slot = player.hotbar[player.selectedHotbarSlot];

        // Determine target tile.
        int tx = 0, ty = 0;
        GetFacingTile(player, tx, ty);

        const int staminaCost = 4;

        switch (slot.type)
        {
            case ItemType::Hoe:
            {
                if (player.stamina < staminaCost) return;
                if (m_farming->Till(tx, ty))
                {
                    player.stamina = std::max(0, player.stamina - staminaCost);
                    player.animState = PlayerAnimState::UseTool;
                }
                break;
            }
            case ItemType::WateringCan:
            {
                if (player.stamina < staminaCost) return;
                if (m_farming->Water(tx, ty))
                {
                    player.stamina = std::max(0, player.stamina - staminaCost);
                    player.animState = PlayerAnimState::UseTool;
                }
                break;
            }
            case ItemType::SeedTurnip:
            {
                if (slot.count <= 0) return;
                if (player.stamina < staminaCost) return;
                if (m_farming->Plant(tx, ty, ItemType::SeedTurnip, kTurnipGrowthDays))
                {
                    player.hotbar[player.selectedHotbarSlot].count -= 1;
                    player.stamina = std::max(0, player.stamina - staminaCost);
                    player.animState = PlayerAnimState::UseTool;
                }
                break;
            }
            default:
            {
                // Empty hand or unrecognised tool: try to harvest.
                DispatchInteract(player);
                break;
            }
        }
    }

    void PlayerManager::DispatchInteract(PlayerState& player)
    {
        if (!m_farming) return;

        int tx = 0, ty = 0;
        GetFacingTile(player, tx, ty);

        ItemType yield = ItemType::None;
        if (m_farming->Harvest(tx, ty, yield) && yield != ItemType::None)
        {
            // Place harvested item in the first available hotbar slot.
            for (int s = 0; s < PlayerState::kHotbarSize; ++s)
            {
                HotbarSlot& slot = player.hotbar[s];
                if (slot.type == yield)
                {
                    slot.count += 1;
                    return;
                }
            }
            for (int s = 0; s < PlayerState::kHotbarSize; ++s)
            {
                HotbarSlot& slot = player.hotbar[s];
                if (slot.type == ItemType::None)
                {
                    slot.type  = yield;
                    slot.count = 1;
                    return;
                }
            }
            // Hotbar full — harvest is lost (acceptable for now).
        }
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

            // --- Hotbar slot selection ---
            if (in.hotbarSlotRequested >= 0 &&
                in.hotbarSlotRequested < PlayerState::kHotbarSize)
            {
                player.selectedHotbarSlot = in.hotbarSlotRequested;
            }
            else if (in.nextHotbarPressed)
            {
                player.selectedHotbarSlot =
                    (player.selectedHotbarSlot + 1) % PlayerState::kHotbarSize;
            }
            else if (in.prevHotbarPressed)
            {
                player.selectedHotbarSlot =
                    (player.selectedHotbarSlot + PlayerState::kHotbarSize - 1)
                    % PlayerState::kHotbarSize;
            }

            // --- Tool use & interaction ---
            if (in.useToolPressed)
            {
                DispatchToolUse(player);
            }
            else if (in.interactPressed)
            {
                DispatchInteract(player);
            }

            // --- Movement ---
            const float vx = in.moveX * moveSpeed;
            const float vy = in.moveY * moveSpeed;

            const float tileSize = static_cast<float>(GameplayRules::TileSize);

            // Axis-separated collision so players can slide along walls.
            const float newX   = player.position.x + vx * dt;
            const int newTileX = static_cast<int>(newX / tileSize);
            const int tileY    = static_cast<int>(player.position.y / tileSize);
            if (!m_collisionGrid || !m_collisionGrid->IsBlocked(newTileX, tileY))
            {
                player.position.x = newX;
            }

            const float newY   = player.position.y + vy * dt;
            const int tileX    = static_cast<int>(player.position.x / tileSize);
            const int newTileY = static_cast<int>(newY / tileSize);
            if (!m_collisionGrid || !m_collisionGrid->IsBlocked(tileX, newTileY))
            {
                player.position.y = newY;
            }

            player.velocity.x = vx;
            player.velocity.y = vy;

            if (vx != 0.0f || vy != 0.0f)
            {
                player.animState = PlayerAnimState::Walk;

                // Update facing from the dominant movement axis.
                // When both axes are equal the vertical direction takes priority
                // (most top-down games favour up/down when moving diagonally).
                if (std::abs(vy) >= std::abs(vx))
                    player.facing = (vy < 0.0f) ? Direction::Up : Direction::Down;
                else
                    player.facing = (vx < 0.0f) ? Direction::Left : Direction::Right;
            }
            else
            {
                // Return to Idle whenever the player is standing still, regardless
                // of what animation state a tool use or other action set.
                player.animState = PlayerAnimState::Idle;
            }
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

