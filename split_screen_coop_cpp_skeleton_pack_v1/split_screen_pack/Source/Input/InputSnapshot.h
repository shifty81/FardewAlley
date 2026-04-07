#pragma once

namespace atlas
{
    struct InputSnapshot
    {
        float moveX = 0.0f;
        float moveY = 0.0f;

        bool interactPressed = false;
        bool useToolPressed = false;
        bool attackPressed = false;
        bool inventoryPressed = false;
        bool menuPressed = false;
        bool confirmPressed = false;
        bool cancelPressed = false;
        bool nextHotbarPressed = false;
        bool prevHotbarPressed = false;
    };
}
