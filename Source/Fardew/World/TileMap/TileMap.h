#pragma once

#include <vector>
#include <string>
#include "Movement/GridPosition.h"
#include "World/TileMap/TileState.h"

namespace Game
{
    class FTileMap
    {
    public:
        FTileMap(int width, int height);

        bool IsInBounds(const FTileCoord& coord) const;
        const FTileState& GetTile(const FTileCoord& coord) const;
        FTileState& GetTileMutable(const FTileCoord& coord);
        void SetTile(const FTileCoord& coord, const FTileState& tile);
        bool IsBlocked(const FTileCoord& coord) const;
        int GetWidth() const noexcept { return Width; }
        int GetHeight() const noexcept { return Height; }
        std::wstring BuildAsciiDebug(const FTileCoord& playerTile, const FTileCoord& targetTile) const;

    private:
        int IndexOf(const FTileCoord& coord) const;

        int Width = 0;
        int Height = 0;
        std::vector<FTileState> Tiles;
        FTileState OutOfBoundsTile { ETileType::Water, EGroundState::None, true, false, false };
    };
}
