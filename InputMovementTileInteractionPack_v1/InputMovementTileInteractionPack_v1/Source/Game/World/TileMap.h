#pragma once

#include <vector>
#include <string>
#include "Game/Movement/GridPosition.h"
#include "Game/World/TileTypes.h"

namespace Game
{
    struct FTile
    {
        ETileType Type = ETileType::Empty;
        bool bBlocked = false;
        bool bInteractable = false;
    };

    class FTileMap
    {
    public:
        FTileMap(int width, int height);

        bool IsInBounds(const FTileCoord& coord) const;
        FTile GetTile(const FTileCoord& coord) const;
        void SetTile(const FTileCoord& coord, const FTile& tile);
        bool IsBlocked(const FTileCoord& coord) const;
        int GetWidth() const noexcept { return Width; }
        int GetHeight() const noexcept { return Height; }
        std::wstring BuildAsciiDebug(const FTileCoord& playerTile) const;

    private:
        int IndexOf(const FTileCoord& coord) const;

        int Width = 0;
        int Height = 0;
        std::vector<FTile> Tiles;
    };
}
