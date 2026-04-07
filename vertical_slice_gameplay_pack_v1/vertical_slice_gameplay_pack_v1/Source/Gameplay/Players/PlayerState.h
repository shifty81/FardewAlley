#pragma once

#include "Core/Types.h"
#include "Math/Vec2.h"

struct PlayerState
{
    int playerIndex = 0;
    EntityId entity = InvalidEntity;
    ZoneId zoneId = InvalidZone;
    Vec2 position{};
    Vec2 velocity{};
    int health = 100;
    int maxHealth = 100;
    int stamina = 100;
    int maxStamina = 100;
    bool inMenu = false;
    bool inDialogue = false;
    bool isUsingContainer = false;
    int money = 0;
};
