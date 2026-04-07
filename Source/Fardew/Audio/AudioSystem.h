#pragma once

#include "../Core/MathTypes.h"

namespace atlas
{
    class AudioSystem
    {
    public:
        void Initialize();
        void UpdateListenerMidpoint(const Vec2& a, const Vec2& b, bool playerAActive, bool playerBActive);

    private:
        Vec2 m_listenerPosition{};
    };
}
