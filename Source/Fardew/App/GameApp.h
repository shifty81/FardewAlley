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
#include <memory>

// Forward-declare VS-namespace types to avoid polluting the atlas header with
// global-namespace aliases from VS_Types.h.
class CollisionGrid;
struct TilemapData;
class FarmingSystem;
namespace TimeSystem { class WorldClock; }

namespace atlas
{
    class GameApp
    {
    public:
        GameApp();
        ~GameApp();

        bool Initialize(const GameConfig& config);
        void RunFrame(float dt);

        bool SaveGame(const char* path);
        bool LoadGame(const char* path);

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

        // Owned subsystems whose headers use VS-namespace global types.
        std::unique_ptr<TimeSystem::WorldClock> m_clock;
        std::unique_ptr<FarmingSystem>          m_farming;
        std::unique_ptr<TilemapData>            m_tilemap;
        std::unique_ptr<CollisionGrid>          m_collision;

        PlayerInputContext m_inputs[2]{};
        HUDContext m_huds[2]{};
    };
}
