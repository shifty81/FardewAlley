#pragma once

#include "../Audio/AudioSystem.h"
#include "../Core/GameConfig.h"
#include "../Core/GameEnums.h"
#include "../Gameplay/Players/PlayerManager.h"
#include "../Gameplay/Session/SessionManager.h"
#include "../Input/PlayerInputContext.h"
#include "../Render/CameraManager.h"
#include "../Render/Renderer2D.h"
#include "../Save/SaveSystem.h"
#include "../UI/HUDContext.h"
#include "../UI/UIManager.h"
#include "../World/Zones/ZoneManager.h"

namespace atlas
{
    class GameApp
    {
    public:
        bool Initialize(const GameConfig& config);
        void RunFrame(float dt);

    private:
        void PollPlatformInput();
        void UpdateUI();
        void UpdateGameplay(float dt);
        void Render();

    private:
        GameMode m_gameMode = GameMode::Boot;
        GameConfig m_config{};

        SessionManager m_sessionManager{};
        PlayerManager m_playerManager{};
        CameraManager m_cameraManager{};
        ZoneManager m_zoneManager{};
        UIManager m_uiManager{};
        Renderer2D m_renderer{};
        SaveSystem m_saveSystem{};
        AudioSystem m_audioSystem{};

        PlayerInputContext m_inputs[2]{};
        HUDContext m_huds[2]{};
    };
}
