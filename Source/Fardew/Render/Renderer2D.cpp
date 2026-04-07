#include "Renderer2D.h"

namespace atlas
{
    void Renderer2D::BeginFrame()
    {
        // TODO: clear backbuffer.
    }

    void Renderer2D::BeginViewport(const ViewportContext&, const Camera2D&)
    {
        // TODO: set viewport, scissor rect, camera matrices.
    }

    void Renderer2D::RenderWorld(int)
    {
        // TODO: render tile layers, entities, particles, world-space prompts.
    }

    void Renderer2D::EndViewport()
    {
    }

    void Renderer2D::RenderGlobalOverlay()
    {
        // TODO: sleep vote, pause overlay, fade, cutscene overlay.
    }

    void Renderer2D::EndFrame()
    {
        // TODO: present swap chain.
    }
}
