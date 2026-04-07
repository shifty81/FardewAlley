#include "Gameplay/VerticalSliceGame.h"
#include "World/Tilemap/TilemapLoader.h"
#include "Gameplay/Interaction/VS_InteractionTypes.h"

bool VerticalSliceGame::Initialize()
{
    TilemapLoader loader;
    if (!loader.LoadFromJson("Data/Maps/vertical_slice_farm.json", m_world.tilemap, m_world.collision))
        return false;

    m_world.farming.Resize(m_world.tilemap.width, m_world.tilemap.height);

    m_world.testChest.interaction.type = InteractionType::Chest;
    m_world.testChest.interaction.requiresExclusiveUse = true;
    m_world.testNpc.type = InteractionType::NPC;
    m_world.testNpc.requiresExclusiveUse = true;

    m_players[0].playerIndex = 0;
    m_players[0].position = { 10.0f, 10.0f };
    m_players[0].money = 100;

    m_players[1].playerIndex = 1;
    m_players[1].position = { 14.0f, 10.0f };
    m_players[1].money = 100;

    m_inventories[0].Add(ItemType::Hoe, 1);
    m_inventories[0].Add(ItemType::WateringCan, 1);
    m_inventories[0].Add(ItemType::SeedTurnip, 5);

    m_inventories[1].Add(ItemType::Hoe, 1);
    m_inventories[1].Add(ItemType::WateringCan, 1);
    m_inventories[1].Add(ItemType::SeedTurnip, 5);

    m_viewports[0] = { 0, 0, 640, 720 };
    m_viewports[1] = { 640, 0, 640, 720 };

    return true;
}

void VerticalSliceGame::Update(float deltaSeconds)
{
    (void)deltaSeconds;
    // Wire input, movement, tile interactions, combat, and locks here.
}

void VerticalSliceGame::Render()
{
    m_renderer.BeginFrame();

    for (int i = 0; i < 2; ++i)
    {
        m_renderer.SetViewport(m_viewports[i]);
        m_renderer.DrawTilemap();
        m_renderer.DrawWorldEntities();
        m_hud.RenderPlayerHUD(m_viewports[i], m_players[i], m_inventories[i]);
    }

    m_hud.RenderGlobalClock(m_world.currentDay, m_world.currentHour, m_world.currentMinute);
    m_renderer.EndFrame();
}

void VerticalSliceGame::AdvanceToNextDay()
{
    ++m_world.currentDay;
    m_world.currentHour = 6;
    m_world.currentMinute = 0;
    m_world.farming.AdvanceDay();
}
