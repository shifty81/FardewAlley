#pragma once

#include "Players/PlayerState_Foundation.h"
#include "../World/WorldModel.h"

namespace Fardew
{
    struct TileDelta
    {
        Int2 Tile{};
        bool TerrainChanged = false;
        TerrainType NewTerrain = TerrainType::Grass;
        bool MoistureChanged = false;
        std::uint8_t NewMoisture = 0;
    };

    struct SpawnedDrop
    {
        ItemStack Stack{};
        Int2 Tile{};
    };

    struct InteractionResult
    {
        ActionType Type = ActionType::None;
        ResultCode Code = ResultCode::Failed;
        std::uint16_t StaminaSpent = 0;
        std::vector<TileDelta> TileChanges;
        std::vector<SpawnedDrop> Drops;
        std::string Message;

        [[nodiscard]] bool Succeeded() const noexcept
        {
            return Code == ResultCode::Success;
        }
    };

    class InteractionService
    {
    public:
        [[nodiscard]] InteractionResult TillTile(PlayerState& player, WorldState& world, const Int2& tile) const;
        [[nodiscard]] InteractionResult WaterTile(PlayerState& player, WorldState& world, const Int2& tile) const;
        [[nodiscard]] InteractionResult PlantSeed(PlayerState& player, WorldState& world, const CropDatabase& crops, const Int2& tile) const;
        [[nodiscard]] InteractionResult HarvestCrop(PlayerState& player, WorldState& world, const CropDatabase& crops, const Int2& tile) const;
        [[nodiscard]] InteractionResult PickupWorldItem(PlayerState& player, WorldState& world, const ItemDatabase& items, EntityId itemEntityId) const;
    };
}
