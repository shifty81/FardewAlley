#include "Render/VS_Renderer2D.h"
#include <iostream>

void Renderer2D::BeginFrame()
{
    std::cout << "BeginFrame\n";
}

void Renderer2D::SetViewport(const ViewportContext& viewport)
{
    std::cout << "SetViewport " << viewport.x << "," << viewport.y << "," << viewport.width << "," << viewport.height << "\n";
}

void Renderer2D::DrawTilemap()
{
    std::cout << "DrawTilemap\n";
}

void Renderer2D::DrawWorldEntities()
{
    std::cout << "DrawWorldEntities\n";
}

void Renderer2D::EndFrame()
{
    std::cout << "EndFrame\n";
}
