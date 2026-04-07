#pragma once

#include "../../Core/GameEnums.h"
#include "../../Core/MathTypes.h"
#include "../../Core/Types.h"
#include "../Inventory/ItemTypes.h"
#include "../../Gameplay/GameplayRules.h"

namespace atlas
{
    struct HotbarSlot
    {
        ItemType type  = ItemType::None;
        int      count = 0;
    };

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

        // Hotbar
        static constexpr int kHotbarSize = GameplayRules::MaxHotbarSlots;
        int selectedHotbarSlot = 0;
        HotbarSlot hotbar[kHotbarSize]{};

        bool isInDialogue = false;
        bool isInMenu = false;
        bool isTransitioning = false;
        bool isActive = false;
    };
}
