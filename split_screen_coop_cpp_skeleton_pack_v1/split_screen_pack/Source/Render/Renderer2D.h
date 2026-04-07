#pragma once

#include "Camera2D.h"
#include "ViewportContext.h"

namespace atlas
{
    class Renderer2D
    {
    public:
        void BeginFrame();
        void BeginViewport(const ViewportContext& viewport, const Camera2D& camera);
        void RenderWorld(int playerIndex);
        void EndViewport();
        void RenderGlobalOverlay();
        void EndFrame();
    };
}
