#pragma once

#include "World/Tilemap/TilemapTypes.h"
#include "World/Tilemap/CollisionGrid.h"
#include <string>

class TilemapLoader
{
public:
    bool LoadFromJson(const std::string& path, TilemapData& outMap, CollisionGrid& outCollision) const;
};
