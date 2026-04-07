#pragma once

#include "Core/Types.h"
#include <vector>
#include <string>

enum class TileLayerType
{
    Ground,
    Decoration,
    Collision,
    Front
};

struct TileLayer
{
    TileLayerType type = TileLayerType::Ground;
    int width = 0;
    int height = 0;
    std::vector<int> tiles;
};

struct TilemapData
{
    std::string name;
    int width = 0;
    int height = 0;
    int tileSize = 16;
    std::vector<TileLayer> layers;
};
