#include "SaveLoad.hpp"

#include <filesystem>
#include <iostream>

using namespace atlasdemo;

static void PrintWorld(const WorldState& world, const std::string& title) {
    std::cout << "\n=== " << title << " ===\n";
    std::cout << "Save Name: " << world.saveName << "\n";
    std::cout << "Day: " << world.clock.dayNumber << " Minute: " << world.clock.minuteOfDay << " TimeScale: " << world.clock.timeScale << " Paused: " << world.clock.paused << "\n";

    std::cout << "Crops: " << world.crops.size() << "\n";
    for (const auto& crop : world.crops) {
        std::cout << "  Crop " << crop.cropId << " at (" << crop.tile.x << ", " << crop.tile.y
                  << ") growth=" << crop.growthDays << "/" << crop.requiredGrowthDays
                  << " wateredToday=" << crop.wateredToday
                  << " harvestReady=" << crop.harvestReady << "\n";
    }

    std::cout << "World Items: " << world.worldItems.size() << "\n";
    for (const auto& item : world.worldItems) {
        std::cout << "  Entity " << item.entityId << " -> " << item.stack.itemId << " x" << item.stack.quantity
                  << " at (" << item.tile.x << ", " << item.tile.y << ") persistent=" << item.persistent
                  << " lifetime=" << item.lifetimeSeconds << "\n";
    }

    std::cout << "Inventory Slots: " << world.inventory.slots.size() << "\n";
    for (const auto& stack : world.inventory.slots) {
        std::cout << "  " << stack.itemId << " x" << stack.quantity << "\n";
    }
}

int main() {
    WorldState world;
    world.saveName = "farm_slot_01";
    world.clock.dayNumber = 4;
    world.clock.minuteOfDay = 1110;
    world.clock.timeScale = 8.0;
    world.clock.paused = false;

    world.crops.push_back(CropTileState{ .tile = {3, 5}, .cropId = "parsnip", .planted = true, .wateredToday = true, .harvestReady = false, .growthDays = 2, .requiredGrowthDays = 4 });
    world.crops.push_back(CropTileState{ .tile = {4, 5}, .cropId = "turnip", .planted = true, .wateredToday = false, .harvestReady = true, .growthDays = 5, .requiredGrowthDays = 5 });

    world.worldItems.push_back(WorldItemEntity{ .entityId = 1001, .stack = {"turnip", 2}, .tile = {4, 5}, .persistent = true, .lifetimeSeconds = -1.0 });
    world.worldItems.push_back(WorldItemEntity{ .entityId = 1002, .stack = {"fiber", 6}, .tile = {7, 2}, .persistent = false, .lifetimeSeconds = 45.0 });

    world.inventory.slots.push_back(ItemStack{"watering_can", 1});
    world.inventory.slots.push_back(ItemStack{"seed_turnip", 8});

    const std::filesystem::path savePath = std::filesystem::current_path() / "data" / "world_save_demo.atlas";
    std::filesystem::create_directories(savePath.parent_path());

    PrintWorld(world, "Before Save");

    if (!SaveLoadService::SaveToFile(world, savePath)) {
        std::cerr << "Failed to save world.\n";
        return 1;
    }

    std::string loadError;
    const auto loaded = SaveLoadService::LoadFromFile(savePath, &loadError);
    if (!loaded.has_value()) {
        std::cerr << "Failed to load world: " << loadError << "\n";
        return 1;
    }

    PrintWorld(*loaded, "After Load");
    std::cout << "\nSave file written to: " << savePath << "\n";
    return 0;
}
