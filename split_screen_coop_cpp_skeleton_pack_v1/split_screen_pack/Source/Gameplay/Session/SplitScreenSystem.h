#pragma once

#include "../../Core/GameEnums.h"
#include "../../Render/ViewportContext.h"

namespace atlas
{
    class SplitScreenSystem
    {
    public:
        void SetPlayerCount(int count);
        void SetMode(SplitMode mode);
        void OnWindowResized(int width, int height);

        bool IsSplitActive() const;
        const ViewportContext& GetViewport(int playerIndex) const;

    private:
        void RecalculateLayout();

    private:
        int m_windowWidth = 1600;
        int m_windowHeight = 900;
        int m_playerCount = 1;
        SplitMode m_mode = SplitMode::None;
        ViewportContext m_viewports[2]{};
    };
}
