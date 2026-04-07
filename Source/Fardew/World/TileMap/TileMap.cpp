#include "World/TileMap/TileMap.h"

namespace Game
{
    FTileMap::FTileMap(int width, int height)
        : Width(width)
        , Height(height)
        , Tiles(static_cast<size_t>(width * height))
    {
    }

    bool FTileMap::IsInBounds(const FTileCoord& coord) const
    {
        return coord.X >= 0 && coord.Y >= 0 && coord.X < Width && coord.Y < Height;
    }

    int FTileMap::IndexOf(const FTileCoord& coord) const
    {
        return coord.Y * Width + coord.X;
    }

    const FTileState& FTileMap::GetTile(const FTileCoord& coord) const
    {
        if (!IsInBounds(coord))
        {
            return OutOfBoundsTile;
        }
        return Tiles[static_cast<size_t>(IndexOf(coord))];
    }

    FTileState& FTileMap::GetTileMutable(const FTileCoord& coord)
    {
        if (!IsInBounds(coord))
        {
            return OutOfBoundsTile;
        }
        return Tiles[static_cast<size_t>(IndexOf(coord))];
    }

    void FTileMap::SetTile(const FTileCoord& coord, const FTileState& tile)
    {
        if (!IsInBounds(coord))
        {
            return;
        }
        Tiles[static_cast<size_t>(IndexOf(coord))] = tile;
    }

    bool FTileMap::IsBlocked(const FTileCoord& coord) const
    {
        return GetTile(coord).bBlocked;
    }

    std::wstring FTileMap::BuildAsciiDebug(const FTileCoord& playerTile, const FTileCoord& targetTile) const
    {
        std::wstring out;
        for (int y = 0; y < Height; ++y)
        {
            for (int x = 0; x < Width; ++x)
            {
                const FTileCoord coord { x, y };
                if (coord == playerTile)
                {
                    out.push_back(L'P');
                    continue;
                }
                if (coord == targetTile)
                {
                    out.push_back(L'X');
                    continue;
                }

                const FTileState& tile = GetTile(coord);
                wchar_t c = L'.';
                if (tile.bHasTree) c = L'T';
                else if (tile.bHasRock) c = L'R';
                else if (tile.BaseType == ETileType::Water) c = L'W';
                else if (tile.GroundState == EGroundState::Watered) c = L'~';
                else if (tile.GroundState == EGroundState::Tilled) c = L'=';
                else if (tile.BaseType == ETileType::Grass) c = L'G';
                else if (tile.BaseType == ETileType::Dirt) c = L'D';
                out.push_back(c);
            }
            if (y + 1 < Height)
            {
                out.push_back(L'|');
            }
        }
        return out;
    }
}
