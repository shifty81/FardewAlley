#include "GameApp.h"

namespace atlas
{
    bool GameApp::Initialize(const GameConfig& config)
    {
        m_config = config;
        m_gameMode = GameMode::InGame;

        m_sessionManager.Initialize(config);
        m_sessionManager.StartLocalCoop();

        m_playerManager.Initialize();
        m_playerManager.ActivatePlayer(0, 1, { 64.0f, 64.0f });
        m_playerManager.ActivatePlayer(1, 1, { 96.0f, 64.0f });

        m_cameraManager.Initialize();
        m_zoneManager.Initialize();
        m_uiManager.Initialize();
        m_audioSystem.Initialize();

        for (int i = 0; i < 2; ++i)
        {
            m_inputs[i].playerIndex = i;
            m_huds[i].playerIndex = i;
        }

        return true;
    }

    void GameApp::RunFrame(float dt)
    {
        PollPlatformInput();
        UpdateUI();
        UpdateGameplay(dt);
        Render();
    }

    void GameApp::PollPlatformInput()
    {
        // TODO: read Win32, SDL, XInput, or your custom platform layer.
        // TODO: populate m_inputs[i].current and preserve previous snapshots.
    }

    void GameApp::UpdateUI()
    {
        for (int i = 0; i < m_sessionManager.GetState().activePlayerCount; ++i)
        {
            const PauseScope pauseScope = m_uiManager.HandleInput(i, m_inputs[i], m_huds[i]);
            if (pauseScope == PauseScope::Global)
            {
                m_sessionManager.GetState().globalPauseActive = m_huds[i].localPauseOpen;
            }
        }

        m_sessionManager.UpdateUIRouting(m_inputs, m_huds);
    }

    void GameApp::UpdateGameplay(float dt)
    {
        if (m_sessionManager.GetState().globalPauseActive)
        {
            return;
        }

        m_playerManager.UpdateGameplayInput(dt, m_inputs);
        m_zoneManager.Update(dt);
        m_cameraManager.Update(m_playerManager, dt);

        const auto& player0 = m_playerManager.GetPlayer(0);
        const auto& player1 = m_playerManager.GetPlayer(1);
        m_audioSystem.UpdateListenerMidpoint(player0.position, player1.position, player0.isActive, player1.isActive);

        // TODO: interaction system, farming, combat, NPC schedules, crop tick, dialogue consequences.
    }

    void GameApp::Render()
    {
        m_renderer.BeginFrame();

        const int count = m_sessionManager.GetState().activePlayerCount;
        const auto& splitSystem = m_sessionManager.GetSplitScreenSystem();

        for (int i = 0; i < count; ++i)
        {
            m_renderer.BeginViewport(splitSystem.GetViewport(i), m_cameraManager.GetCamera(i));
            m_renderer.RenderWorld(i);
            m_uiManager.RenderHUD(i);
            m_renderer.EndViewport();
        }

        m_renderer.RenderGlobalOverlay();
        m_renderer.EndFrame();
    }
}
