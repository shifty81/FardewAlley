#include "WorldModel.h"

namespace Fardew
{
    TileState* ChunkState::TryGetTile(int localX, int localY)
    {
        if (localX < 0 || localX >= kChunkWidth || localY < 0 || localY >= kChunkHeight)
        {
            return nullptr;
        }
        return &Tiles[static_cast<std::size_t>(localY * kChunkWidth + localX)];
    }

    const TileState* ChunkState::TryGetTile(int localX, int localY) const
    {
        if (localX < 0 || localX >= kChunkWidth || localY < 0 || localY >= kChunkHeight)
        {
            return nullptr;
        }
        return &Tiles[static_cast<std::size_t>(localY * kChunkWidth + localX)];
    }

    ChunkId WorldState::MakeChunkId(const Int2& coord) noexcept
    {
        return (static_cast<std::uint32_t>(coord.X) & 0xFFFFu) << 16 |
               (static_cast<std::uint32_t>(coord.Y) & 0xFFFFu);
    }

    ChunkState& WorldState::GetOrCreateChunk(const Int2& chunkCoord)
    {
        const ChunkId id = MakeChunkId(chunkCoord);
        auto [it, inserted] = m_Chunks.try_emplace(id);
        if (inserted)
        {
            it->second.Id = id;
            it->second.ChunkCoord = chunkCoord;
        }
        return it->second;
    }

    TileState* WorldState::TryGetTile(const Int2& worldTile)
    {
        const Int2 chunkCoord{ worldTile.X / kChunkWidth, worldTile.Y / kChunkHeight };
        const int localX = ((worldTile.X % kChunkWidth) + kChunkWidth) % kChunkWidth;
        const int localY = ((worldTile.Y % kChunkHeight) + kChunkHeight) % kChunkHeight;
        auto it = m_Chunks.find(MakeChunkId(chunkCoord));
        return it != m_Chunks.end() ? it->second.TryGetTile(localX, localY) : nullptr;
    }

    const TileState* WorldState::TryGetTile(const Int2& worldTile) const
    {
        const Int2 chunkCoord{ worldTile.X / kChunkWidth, worldTile.Y / kChunkHeight };
        const int localX = ((worldTile.X % kChunkWidth) + kChunkWidth) % kChunkWidth;
        const int localY = ((worldTile.Y % kChunkHeight) + kChunkHeight) % kChunkHeight;
        auto it = m_Chunks.find(MakeChunkId(chunkCoord));
        return it != m_Chunks.end() ? it->second.TryGetTile(localX, localY) : nullptr;
    }
}
