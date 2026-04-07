#include "SessionManager.h"

namespace atlas
{
    void SessionManager::Initialize(const GameConfig& config)
    {
        m_config = config;
        m_splitScreenSystem.OnWindowResized(config.windowWidth, config.windowHeight);
        StartSinglePlayer();
    }

    void SessionManager::StartSinglePlayer()
    {
        m_state.mode = SessionMode::SinglePlayer;
        m_state.splitMode = SplitMode::None;
        m_state.activePlayerCount = 1;
        m_state.globalPauseActive = false;
        m_splitScreenSystem.SetPlayerCount(1);
        m_splitScreenSystem.SetMode(SplitMode::None);
    }

    void SessionManager::StartLocalCoop()
    {
        m_state.mode = SessionMode::LocalCoop2P;
        m_state.splitMode = SplitMode::FixedVertical;
        m_state.activePlayerCount = 2;
        m_state.globalPauseActive = false;
        m_splitScreenSystem.SetPlayerCount(2);
        m_splitScreenSystem.SetMode(SplitMode::FixedVertical);
    }

    void SessionManager::AssignInputDevice(int, int)
    {
        // TODO: persist device ownership, support rebind flow.
    }

    void SessionManager::UpdateUIRouting(PlayerInputContext[2], HUDContext[2])
    {
        // TODO: enforce session-level menu rules and global pause policy.
    }

    SessionState& SessionManager::GetState()
    {
        return m_state;
    }

    const SessionState& SessionManager::GetState() const
    {
        return m_state;
    }

    SplitScreenSystem& SessionManager::GetSplitScreenSystem()
    {
        return m_splitScreenSystem;
    }

    const SplitScreenSystem& SessionManager::GetSplitScreenSystem() const
    {
        return m_splitScreenSystem;
    }

    bool SessionManager::AreAllActivePlayersReadyForSleep() const
    {
        for (int i = 0; i < m_state.activePlayerCount; ++i)
        {
            if (!m_state.playerReadyForSleep[i])
            {
                return false;
            }
        }

        return true;
    }
}
