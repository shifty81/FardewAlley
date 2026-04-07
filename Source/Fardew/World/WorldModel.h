#pragma once

#include "../Core/Tile.h"
#include "../Data/CropData.h"
#include "../Data/ItemData.h"
#include <unordered_map>

namespace Fardew
{
    constexpr int kChunkWidth = 32;
    constexpr int kChunkHeight = 32;

    struct WorldItemEntity
    {
        EntityId Id = 0;
        ItemStack Stack{};
        Int2 Tile{};
        std::uint16_t LifetimeTicks = 0;
        PlayerId ReservedForPlayerId = 0;
    };

    struct ChunkState
    {
        ChunkId Id = 0;
        Int2 ChunkCoord{};
        std::array<TileState, kChunkWidth * kChunkHeight> Tiles{};

        [[nodiscard]] TileState* TryGetTile(int localX, int localY);
        [[nodiscard]] const TileState* TryGetTile(int localX, int localY) const;
    };

    class WorldState
    {
    public:
        ChunkState& GetOrCreateChunk(const Int2& chunkCoord);
        TileState* TryGetTile(const Int2& worldTile);
        const TileState* TryGetTile(const Int2& worldTile) const;

        std::unordered_map<EntityId, CropInstance> Crops;
        std::unordered_map<EntityId, WorldItemEntity> WorldItems;

    private:
        [[nodiscard]] static ChunkId MakeChunkId(const Int2& coord) noexcept;
        std::unordered_map<ChunkId, ChunkState> m_Chunks;
    };
}
