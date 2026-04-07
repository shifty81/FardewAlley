#pragma once

#include "UI/HUDRenderer.h"

class Renderer2D
{
public:
    void BeginFrame();
    void SetViewport(const ViewportContext& viewport);
    void DrawTilemap();
    void DrawWorldEntities();
    void EndFrame();
};
