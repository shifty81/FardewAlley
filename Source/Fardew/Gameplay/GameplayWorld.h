#pragma once

#include "World/Tilemap/TilemapTypes.h"
#include "World/Tilemap/CollisionGrid.h"
#include "Gameplay/Farming/VS_FarmingSystem.h"
#include "Gameplay/Interaction/ChestSystem.h"
#include "Gameplay/Interaction/VS_InteractionComponent.h"

struct GameplayWorld
{
    TilemapData tilemap;
    CollisionGrid collision;
    FarmingSystem farming;
    ChestState testChest;
    InteractionComponent testNpc;
    int currentDay = 1;
    int currentHour = 6;
    int currentMinute = 0;
};
