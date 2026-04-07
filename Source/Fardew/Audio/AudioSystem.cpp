#include "AudioSystem.h"

namespace atlas
{
    void AudioSystem::Initialize()
    {
    }

    void AudioSystem::UpdateListenerMidpoint(const Vec2& a, const Vec2& b, bool playerAActive, bool playerBActive)
    {
        if (playerAActive && playerBActive)
        {
            m_listenerPosition.x = (a.x + b.x) * 0.5f;
            m_listenerPosition.y = (a.y + b.y) * 0.5f;
            return;
        }

        if (playerAActive)
        {
            m_listenerPosition = a;
            return;
        }

        if (playerBActive)
        {
            m_listenerPosition = b;
        }
    }
}
