#pragma once

#include "../../Core/GameEnums.h"
#include "../../Core/MathTypes.h"
#include "../../Core/Types.h"

namespace atlas
{
    struct ZoneTransition
    {
        ZoneTransitionType type = ZoneTransitionType::Door;
        TransitionRequirement requirement = TransitionRequirement::LocalOnly;

        ZoneId sourceZone = InvalidZoneId;
        ZoneId targetZone = InvalidZoneId;
        Vec2 targetSpawnPosition{};
    };
}
