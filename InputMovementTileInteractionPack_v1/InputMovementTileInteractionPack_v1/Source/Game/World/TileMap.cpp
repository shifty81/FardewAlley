#include "Game/World/TileMap.h"

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

    FTile FTileMap::GetTile(const FTileCoord& coord) const
    {
        if (!IsInBounds(coord))
        {
            return { ETileType::Rock, true, false };
        }
        return Tiles[static_cast<size_t>(IndexOf(coord))];
    }

    void FTileMap::SetTile(const FTileCoord& coord, const FTile& tile)
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

    std::wstring FTileMap::BuildAsciiDebug(const FTileCoord& playerTile) const
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

                const FTile tile = GetTile(coord);
                wchar_t c = L'.';
                switch (tile.Type)
                {
                    case ETileType::Grass: c = L'G'; break;
                    case ETileType::Dirt: c = L'D'; break;
                    case ETileType::Water: c = L'W'; break;
                    case ETileType::Rock: c = L'R'; break;
                    case ETileType::Tree: c = L'T'; break;
                    case ETileType::TilledDirt: c = L'='; break;
                    case ETileType::Stump: c = L's'; break;
                    default: c = L'.'; break;
                }
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
