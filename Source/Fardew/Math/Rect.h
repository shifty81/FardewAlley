#pragma once

struct Rect
{
    float x = 0.0f;
    float y = 0.0f;
    float w = 0.0f;
    float h = 0.0f;

    bool Contains(float px, float py) const
    {
        return px >= x && py >= y && px < (x + w) && py < (y + h);
    }
};
