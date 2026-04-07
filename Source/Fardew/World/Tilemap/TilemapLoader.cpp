#include "World/Tilemap/TilemapLoader.h"

bool TilemapLoader::LoadFromJson(const std::string& path, TilemapData& outMap, CollisionGrid& outCollision) const
{
    (void)path;

    // Stub only. Replace with real JSON parsing.
    outMap.name = "VerticalSlice_Farm";
    outMap.width = 64;
    outMap.height = 64;
    outMap.tileSize = 16;

    outCollision.Resize(outMap.width, outMap.height);

    for (int x = 0; x < outMap.width; ++x)
    {
        outCollision.SetBlocked(x, 0, true);
        outCollision.SetBlocked(x, outMap.height - 1, true);
    }
    for (int y = 0; y < outMap.height; ++y)
    {
        outCollision.SetBlocked(0, y, true);
        outCollision.SetBlocked(outMap.width - 1, y, true);
    }

    return true;
}
