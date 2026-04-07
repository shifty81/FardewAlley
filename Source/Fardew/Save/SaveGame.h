#pragma once

#include "../Gameplay/CoopRules.h"
#include "../World/WorldModel.h"

namespace Fardew
{
    struct SaveMetadata
    {
        std::string SlotName;
        std::uint32_t SaveVersion = 1;
        Season CurrentSeason = Season::Spring;
        std::uint32_t DayOfSeason = 1;
        std::uint32_t ClockMinutes = 360;
    };

    struct SaveGame
    {
        SaveMetadata Meta;
        CoopSessionState Session;
        WorldState World;
    };
}
