#pragma once

#include <array>
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace Fardew
{
    using ItemId = std::uint32_t;
    using CropId = std::uint32_t;
    using PlayerId = std::uint32_t;
    using EntityId = std::uint64_t;
    using ChunkId = std::uint32_t;
    using TileCoord = std::int32_t;

    struct Int2
    {
        int X = 0;
        int Y = 0;

        constexpr bool operator==(const Int2& rhs) const noexcept
        {
            return X == rhs.X && Y == rhs.Y;
        }
    };

    enum class Facing : std::uint8_t
    {
        Down,
        Left,
        Right,
        Up
    };

    enum class Season : std::uint8_t
    {
        Spring,
        Summer,
        Fall,
        Winter
    };

    enum class TerrainType : std::uint8_t
    {
        Grass,
        Dirt,
        Tilled,
        Water,
        Stone,
        Path
    };

    enum class ItemCategory : std::uint8_t
    {
        None,
        Tool,
        Seed,
        Crop,
        Material,
        Placeable,
        Consumable
    };

    enum class ToolType : std::uint8_t
    {
        None,
        Hoe,
        WateringCan,
        Axe,
        Pickaxe,
        Scythe
    };

    enum class ActionType : std::uint8_t
    {
        None,
        Interact,
        UseTool,
        PickupItem,
        DropItem,
        PlantSeed,
        HarvestCrop,
        PlaceObject,
        OpenContainer
    };

    enum class ResultCode : std::uint8_t
    {
        Success,
        NoTarget,
        InvalidTarget,
        Blocked,
        InventoryFull,
        OutOfRange,
        NotEnoughStamina,
        InvalidItem,
        Failed
    };
}
