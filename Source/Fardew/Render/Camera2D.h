#pragma once

#include "../Core/MathTypes.h"
#include "../Core/Types.h"

namespace atlas
{
    struct Camera2D
    {
        Vec2 position{};
        Vec2 targetPosition{};
        Vec2 velocity{};
        float zoom = 1.0f;
        Rect worldBounds{};
        Rect deadZone{};
        float smoothTime = 0.10f;
        bool clampToBounds = true;
        EntityId followTarget = InvalidEntityId;
        ZoneId currentZone = InvalidZoneId;
    };
}
