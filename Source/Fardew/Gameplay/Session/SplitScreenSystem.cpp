#include "SplitScreenSystem.h"

namespace atlas
{
    void SplitScreenSystem::SetPlayerCount(int count)
    {
        m_playerCount = count;
        RecalculateLayout();
    }

    void SplitScreenSystem::SetMode(SplitMode mode)
    {
        m_mode = mode;
        RecalculateLayout();
    }

    void SplitScreenSystem::OnWindowResized(int width, int height)
    {
        m_windowWidth = width;
        m_windowHeight = height;
        RecalculateLayout();
    }

    bool SplitScreenSystem::IsSplitActive() const
    {
        return m_playerCount > 1 && m_mode == SplitMode::FixedVertical;
    }

    const ViewportContext& SplitScreenSystem::GetViewport(int playerIndex) const
    {
        return m_viewports[playerIndex];
    }

    void SplitScreenSystem::RecalculateLayout()
    {
        constexpr int safePadding = 16;

        if (!IsSplitActive())
        {
            m_viewports[0].playerIndex = 0;
            m_viewports[0].viewportRect = { 0, 0, m_windowWidth, m_windowHeight };
            m_viewports[0].safeAreaRect = { safePadding, safePadding, m_windowWidth - safePadding * 2, m_windowHeight - safePadding * 2 };

            m_viewports[1].playerIndex = 1;
            m_viewports[1].viewportRect = { 0, 0, 0, 0 };
            m_viewports[1].safeAreaRect = { 0, 0, 0, 0 };
            return;
        }

        const int halfWidth = m_windowWidth / 2;

        m_viewports[0].playerIndex = 0;
        m_viewports[0].viewportRect = { 0, 0, halfWidth, m_windowHeight };
        m_viewports[0].safeAreaRect = { safePadding, safePadding, halfWidth - safePadding * 2, m_windowHeight - safePadding * 2 };

        m_viewports[1].playerIndex = 1;
        m_viewports[1].viewportRect = { halfWidth, 0, m_windowWidth - halfWidth, m_windowHeight };
        m_viewports[1].safeAreaRect = { halfWidth + safePadding, safePadding, (m_windowWidth - halfWidth) - safePadding * 2, m_windowHeight - safePadding * 2 };
    }
}
