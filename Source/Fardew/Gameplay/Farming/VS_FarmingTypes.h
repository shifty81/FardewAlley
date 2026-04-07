#pragma once

#include "Gameplay/Inventory/ItemTypes.h"

enum class SoilState
{
    Untilled,
    Tilled
};

struct FarmingTileState
{
    SoilState soil = SoilState::Untilled;
    bool wateredToday = false;
    bool hasCrop = false;
    ItemType cropSeedType = ItemType::None;
    int growthDay = 0;
    int daysToHarvest = 0;
    bool harvestReady = false;
};
