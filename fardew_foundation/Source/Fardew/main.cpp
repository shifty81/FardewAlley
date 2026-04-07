#include "Data/CropData.h"
#include "Data/ItemData.h"
#include "Gameplay/Interaction.h"
#include "Gameplay/WorldModel.h"
#include "Save/SaveSerializer.h"
#include <iostream>

int main()
{
    using namespace Fardew;

    ItemDatabase items;
    items.Register({ 1, "Parsnip Seeds", ItemCategory::Seed, ToolType::None, 99, 5, 100 });
    items.Register({ 2, "Parsnip", ItemCategory::Crop, ToolType::None, 99, 35, 0 });

    CropDatabase crops;
    CropDefinition parsnip;
    parsnip.Id = 100;
    parsnip.Name = "Parsnip";
    parsnip.SeedItemId = 1;
    parsnip.HarvestItemId = 2;
    parsnip.StageDays = { 1, 1, 1, 1 };
    parsnip.ValidSeasons = { true, false, false, false };
    crops.Register(parsnip);

    WorldState world;
    TileState* tile = world.GetOrCreateChunk({ 0, 0 }).TryGetTile(5, 5);
    tile->Terrain = TerrainType::Dirt;
    tile->Flags = TileFlag_Tillable | TileFlag_Waterable;

    PlayerState player;
    player.Id = 1;
    player.Viewport.IsHost = true;
    player.Bag.Slots[0] = { 1, 5 };

    InteractionService interaction;
    std::cout << interaction.TillTile(player, world, { 5, 5 }).Message << '\n';
    std::cout << interaction.WaterTile(player, world, { 5, 5 }).Message << '\n';
    std::cout << interaction.PlantSeed(player, world, crops, { 5, 5 }).Message << '\n';

    if (TileState* plantedTile = world.TryGetTile({ 5, 5 }))
    {
        auto cropIt = world.Crops.find(plantedTile->CropInstanceId);
        if (cropIt != world.Crops.end())
        {
            cropIt->second.HarvestReady = true;
            const auto harvest = interaction.HarvestCrop(player, world, crops, { 5, 5 });
            std::cout << harvest.Message << '\n';
            for (const SpawnedDrop& drop : harvest.Drops)
            {
                world.WorldItems[1] = { 1, drop.Stack, drop.Tile, 1000, 0 };
            }
        }
    }

    std::cout << interaction.PickupWorldItem(player, world, items, 1).Message << '\n';

    SaveGame save;
    save.Meta.SlotName = "TestFarm";
    save.Session.Players[0] = player;
    save.World = world;

    SaveSerializer serializer;
    std::cout << serializer.Serialize(save);
    return 0;
}
