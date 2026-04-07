#pragma once

#include "../Core/MathTypes.h"
#include "../Core/Types.h"

namespace atlas
{
    struct PlayerSaveData
    {
        bool occupied = false;
        ZoneId zone = InvalidZoneId;
        Vec2 position{};
        int health = 100;
        int stamina = 100;
        InventoryId inventory = InvalidInventoryId;
    };

    struct WorldSaveData
    {
        int dayNumber = 1;
        int clockMinuteOfDay = 360; // 06:00 default
        int weatherType = 0;
        // TODO: crops, placed objects, NPC relationship state, chest state, quest state.
    };

    struct SaveGameData
    {
        WorldSaveData world;
        PlayerSaveData players[2];
    };
}
