#pragma once

#include "SplitScreen_PlayerState.h"
#include "../../Input/PlayerInputContext.h"
#include "../../World/Zones/ZoneTransition.h"

class CollisionGrid;  // forward declaration — full type included in .cpp

namespace atlas
{
    class PlayerManager
    {
    public:
        void Initialize();
        void ActivatePlayer(int playerIndex, ZoneId zone, Vec2 spawnPosition);
        void DeactivatePlayer(int playerIndex);

        void SetCollisionGrid(const CollisionGrid* grid);
        void UpdateGameplayInput(float dt, const PlayerInputContext inputs[2]);
        void ApplyZoneTransition(int playerIndex, const ZoneTransition& transition);

        PlayerState& GetPlayer(int playerIndex);
        const PlayerState& GetPlayer(int playerIndex) const;
        const PlayerState* GetPlayers() const { return m_players; }
        static constexpr int kMaxPlayers = 2;

    private:
        PlayerState m_players[2]{};
        const CollisionGrid* m_collisionGrid = nullptr;
    };
}
