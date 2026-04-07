#pragma once

#include "SessionState.h"
#include "SplitScreenSystem.h"
#include "../../Input/PlayerInputContext.h"
#include "../../UI/HUDContext.h"
#include "../../Core/GameConfig.h"

namespace atlas
{
    class SessionManager
    {
    public:
        void Initialize(const GameConfig& config);
        void StartSinglePlayer();
        void StartLocalCoop();

        void AssignInputDevice(int playerIndex, int deviceId);
        void UpdateUIRouting(PlayerInputContext inputs[2], HUDContext huds[2]);

        SessionState& GetState();
        const SessionState& GetState() const;
        SplitScreenSystem& GetSplitScreenSystem();
        const SplitScreenSystem& GetSplitScreenSystem() const;

        bool AreAllActivePlayersReadyForSleep() const;

    private:
        SessionState m_state{};
        SplitScreenSystem m_splitScreenSystem{};
        GameConfig m_config{};
    };
}
