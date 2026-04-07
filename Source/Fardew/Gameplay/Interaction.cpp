#include "Interaction.h"

namespace Fardew
{
    namespace
    {
        InteractionResult Fail(ActionType type, ResultCode code, std::string message)
        {
            InteractionResult result;
            result.Type = type;
            result.Code = code;
            result.Message = std::move(message);
            return result;
        }
    }

    InteractionResult InteractionService::TillTile(PlayerState& player, WorldState& world, const Int2& tile) const
    {
        TileState* target = world.TryGetTile(tile);
        if (target == nullptr)
        {
            return Fail(ActionType::UseTool, ResultCode::NoTarget, "Tile not found.");
        }
        if ((target->Flags & TileFlag_Tillable) == 0 || target->HasCrop() || target->HasPlaceable())
        {
            return Fail(ActionType::UseTool, ResultCode::InvalidTarget, "Tile cannot be tilled.");
        }
        if (player.Stamina < 2)
        {
            return Fail(ActionType::UseTool, ResultCode::NotEnoughStamina, "Not enough stamina.");
        }

        player.Stamina -= 2;
        target->Terrain = TerrainType::Tilled;
        target->Flags |= TileFlag_Waterable | TileFlag_Plantable;

        InteractionResult result;
        result.Type = ActionType::UseTool;
        result.Code = ResultCode::Success;
        result.StaminaSpent = 2;
        result.TileChanges.push_back({ tile, true, TerrainType::Tilled, false, 0 });
        result.Message = "Tile tilled.";
        return result;
    }

    InteractionResult InteractionService::WaterTile(PlayerState& player, WorldState& world, const Int2& tile) const
    {
        TileState* target = world.TryGetTile(tile);
        if (target == nullptr)
        {
            return Fail(ActionType::UseTool, ResultCode::NoTarget, "Tile not found.");
        }
        if ((target->Flags & TileFlag_Waterable) == 0)
        {
            return Fail(ActionType::UseTool, ResultCode::InvalidTarget, "Tile cannot be watered.");
        }
        if (player.Stamina < 1)
        {
            return Fail(ActionType::UseTool, ResultCode::NotEnoughStamina, "Not enough stamina.");
        }

        player.Stamina -= 1;
        target->Moisture = 255;

        InteractionResult result;
        result.Type = ActionType::UseTool;
        result.Code = ResultCode::Success;
        result.StaminaSpent = 1;
        result.TileChanges.push_back({ tile, false, TerrainType::Grass, true, 255 });
        result.Message = "Tile watered.";
        return result;
    }

    InteractionResult InteractionService::PlantSeed(PlayerState& player, WorldState& world, const CropDatabase& crops, const Int2& tile) const
    {
        TileState* target = world.TryGetTile(tile);
        if (target == nullptr)
        {
            return Fail(ActionType::PlantSeed, ResultCode::NoTarget, "Tile not found.");
        }
        if ((target->Flags & TileFlag_Plantable) == 0 || target->HasCrop())
        {
            return Fail(ActionType::PlantSeed, ResultCode::InvalidTarget, "Tile cannot accept a seed.");
        }

        ItemStack held = player.GetSelectedItem();
        const CropDefinition* crop = crops.FindBySeed(held.Id);
        if (crop == nullptr)
        {
            return Fail(ActionType::PlantSeed, ResultCode::InvalidItem, "Selected item is not a seed.");
        }

        ItemStack removed = player.Bag.RemoveFromSlot(player.SelectedHotbarSlot, 1);
        if (removed.Count == 0)
        {
            return Fail(ActionType::PlantSeed, ResultCode::InvalidItem, "Seed could not be removed.");
        }

        const EntityId cropEntityId = static_cast<EntityId>(world.Crops.size() + 1);
        CropInstance instance;
        instance.InstanceId = cropEntityId;
        instance.DefinitionId = crop->Id;
        instance.Tile = tile;
        world.Crops[cropEntityId] = instance;
        target->CropInstanceId = cropEntityId;

        InteractionResult result;
        result.Type = ActionType::PlantSeed;
        result.Code = ResultCode::Success;
        result.Message = "Seed planted.";
        return result;
    }

    InteractionResult InteractionService::HarvestCrop(PlayerState& player, WorldState& world, const CropDatabase& crops, const Int2& tile) const
    {
        TileState* target = world.TryGetTile(tile);
        if (target == nullptr || !target->HasCrop())
        {
            return Fail(ActionType::HarvestCrop, ResultCode::NoTarget, "No crop to harvest.");
        }

        auto it = world.Crops.find(target->CropInstanceId);
        if (it == world.Crops.end() || !it->second.HarvestReady)
        {
            return Fail(ActionType::HarvestCrop, ResultCode::InvalidTarget, "Crop is not ready.");
        }

        const CropDefinition* crop = crops.Find(it->second.DefinitionId);
        if (crop == nullptr)
        {
            return Fail(ActionType::HarvestCrop, ResultCode::InvalidTarget, "Crop definition missing.");
        }

        InteractionResult result;
        result.Type = ActionType::HarvestCrop;
        result.Code = ResultCode::Success;
        result.Drops.push_back({ ItemStack{ crop->HarvestItemId, 1 }, tile });
        result.Message = "Crop harvested.";

        target->CropInstanceId = 0;
        world.Crops.erase(it);
        return result;
    }

    InteractionResult InteractionService::PickupWorldItem(PlayerState& player, WorldState& world, const ItemDatabase& items, EntityId itemEntityId) const
    {
        auto it = world.WorldItems.find(itemEntityId);
        if (it == world.WorldItems.end())
        {
            return Fail(ActionType::PickupItem, ResultCode::NoTarget, "World item not found.");
        }

        if (!player.Bag.AddItem(items, it->second.Stack))
        {
            return Fail(ActionType::PickupItem, ResultCode::InventoryFull, "Inventory full.");
        }

        world.WorldItems.erase(it);
        InteractionResult result;
        result.Type = ActionType::PickupItem;
        result.Code = ResultCode::Success;
        result.Message = "Item picked up.";
        return result;
    }
}
