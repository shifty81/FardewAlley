#pragma once

#include "../../Core/GameEnums.h"
#include "../../Core/MathTypes.h"
#include "../../Core/Types.h"

namespace atlas
{
    struct PlayerState
    {
        EntityId entity = InvalidEntityId;
        int playerIndex = -1;
        ZoneId zone = InvalidZoneId;

        Vec2 position{};
        Vec2 velocity{};
        Direction facing = Direction::Down;
        PlayerAnimState animState = PlayerAnimState::Idle;

        int health = 100;
        int maxHealth = 100;
        int stamina = 100;
        int maxStamina = 100;

        InventoryId inventory = InvalidInventoryId;

        bool isInDialogue = false;
        bool isInMenu = false;
        bool isTransitioning = false;
        bool isActive = false;
    };
}
