#include "GameApp.h"
#include "../Time/TimeSystem.hpp"
#include "../Gameplay/Farming/VS_FarmingSystem.h"
#include "../World/Tilemap/TilemapLoader.h"
#include "../World/Tilemap/CollisionGrid.h"
#include "../World/Tilemap/TilemapTypes.h"
#include <SDL2/SDL.h>

namespace atlas
{
    GameApp::GameApp() = default;

    GameApp::~GameApp()
    {
        if (m_sdlRenderer) SDL_DestroyRenderer(m_sdlRenderer);
        if (m_sdlWindow)   SDL_DestroyWindow(m_sdlWindow);
        SDL_Quit();
    }

    bool GameApp::Initialize(const GameConfig& config)
    {
        m_config = config;
        m_gameMode = GameMode::InGame;

        // --- SDL ---
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            return false;
        }

        m_sdlWindow = SDL_CreateWindow(
            "Fardew Alley",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            config.windowWidth, config.windowHeight,
            SDL_WINDOW_SHOWN | (config.startInFullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0));
        if (!m_sdlWindow) return false;

        m_sdlRenderer = SDL_CreateRenderer(
            m_sdlWindow, -1,
            SDL_RENDERER_ACCELERATED | (config.vsyncEnabled ? SDL_RENDERER_PRESENTVSYNC : 0));
        if (!m_sdlRenderer) return false;

        // Create and configure the world clock (default: 06:00 on day 1).
        m_clock    = std::make_unique<TimeSystem::WorldClock>();
        m_tilemap  = std::make_unique<TilemapData>();
        m_collision = std::make_unique<CollisionGrid>();
        m_farming  = std::make_unique<FarmingSystem>();

        // Load the farm tilemap (stub loader sets up a 64x64 map with border walls).
        TilemapLoader loader;
        loader.LoadFromJson("Data/Maps/farm.json", *m_tilemap, *m_collision);
        m_farming->Resize(m_tilemap->width, m_tilemap->height);

        m_sessionManager.Initialize(config);
        m_sessionManager.StartLocalCoop();

        m_playerManager.Initialize();
        m_playerManager.SetCollisionGrid(m_collision.get());
        m_playerManager.ActivatePlayer(0, 1, { 64.0f, 64.0f });
        m_playerManager.ActivatePlayer(1, 1, { 96.0f, 64.0f });

        m_cameraManager.Initialize();
        m_zoneManager.Initialize();
        m_uiManager.Initialize();
        m_audioSystem.Initialize();

        // Wire renderer with SDL context and world data.
        m_renderer.Init(m_sdlRenderer, m_sdlWindow);
        m_renderer.SetWorldContext(
            m_tilemap.get(), m_collision.get(), m_farming.get(),
            m_playerManager.GetPlayers(), PlayerManager::kMaxPlayers);

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
        // Preserve previous snapshot so callers can detect "just pressed" edges.
        for (int i = 0; i < 2; ++i)
        {
            m_inputs[i].previous = m_inputs[i].current;
            // Reset single-frame action flags; movement is re-read from held keys below.
            m_inputs[i].current.interactPressed  = false;
            m_inputs[i].current.useToolPressed   = false;
            m_inputs[i].current.inventoryPressed = false;
            m_inputs[i].current.menuPressed      = false;
        }

        // Drain the SDL event queue — detect key-down edges and quit events.
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                m_gameMode = GameMode::ShuttingDown;
            }

            if (event.type == SDL_KEYDOWN && !event.key.repeat)
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:  m_gameMode = GameMode::ShuttingDown;       break;
                    // Player 0 (WASD) action keys
                    case SDLK_e:       m_inputs[0].current.interactPressed = true; break;
                    case SDLK_SPACE:   m_inputs[0].current.useToolPressed   = true; break;
                    case SDLK_f:       m_inputs[0].current.inventoryPressed = true; break;
                    case SDLK_TAB:     m_inputs[0].current.menuPressed      = true; break;
                    // Player 1 (arrows) action keys
                    case SDLK_RCTRL:   m_inputs[1].current.interactPressed = true; break;
                    case SDLK_RSHIFT:  m_inputs[1].current.useToolPressed   = true; break;
                    case SDLK_SLASH:   m_inputs[1].current.inventoryPressed = true; break;
                    default: break;
                }
            }
        }

        // Continuous movement from held keys (SDL_GetKeyboardState is always up-to-date).
        const Uint8* keys = SDL_GetKeyboardState(nullptr);

        // Player 0 — WASD
        {
            float dx = 0.0f, dy = 0.0f;
            if (keys[SDL_SCANCODE_W]) dy -= 1.0f;
            if (keys[SDL_SCANCODE_S]) dy += 1.0f;
            if (keys[SDL_SCANCODE_A]) dx -= 1.0f;
            if (keys[SDL_SCANCODE_D]) dx += 1.0f;
            m_inputs[0].current.moveX = dx;
            m_inputs[0].current.moveY = dy;
        }

        // Player 1 — Arrow keys
        {
            float dx = 0.0f, dy = 0.0f;
            if (keys[SDL_SCANCODE_UP])    dy -= 1.0f;
            if (keys[SDL_SCANCODE_DOWN])  dy += 1.0f;
            if (keys[SDL_SCANCODE_LEFT])  dx -= 1.0f;
            if (keys[SDL_SCANCODE_RIGHT]) dx += 1.0f;
            m_inputs[1].current.moveX = dx;
            m_inputs[1].current.moveY = dy;
        }
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

        // Advance the world clock and react to day boundaries.
        const TimeSystem::TickResult tick = m_clock->TickRealtime(static_cast<double>(dt));
        if (tick.crossedDay)
        {
            m_farming->AdvanceDay();
        }

        // TODO: interaction system, combat, NPC schedules, dialogue consequences.
    }

    bool GameApp::SaveGame(const char* path)
    {
        SaveGameData saveData;
        m_saveSystem.CaptureFromWorld(m_playerManager, saveData);

        // Persist clock state alongside player data.
        const TimeSystem::ClockStamp& stamp = m_clock->GetStamp();
        saveData.world.dayNumber      = stamp.dayIndex;
        saveData.world.clockMinuteOfDay = stamp.minuteOfDay;

        return m_saveSystem.SaveToDisk(path, saveData);
    }

    bool GameApp::LoadGame(const char* path)
    {
        SaveGameData saveData;
        if (!m_saveSystem.LoadFromDisk(path, saveData))
        {
            return false;
        }

        m_saveSystem.ApplyToWorld(saveData, m_playerManager);

        // Restore the world clock from saved state.
        TimeSystem::ClockStamp stamp;
        stamp.dayIndex    = saveData.world.dayNumber;
        stamp.minuteOfDay = saveData.world.clockMinuteOfDay;
        m_clock->SetStamp(stamp);

        return true;
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

        m_renderer.RenderGlobalOverlay(count);
        m_renderer.EndFrame();
    }
}
