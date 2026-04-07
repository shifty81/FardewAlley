#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace atlas {

struct Vec2i {
    int x = 0;
    int y = 0;
};

struct ItemStack {
    std::string itemId;
    int quantity = 0;
};

struct CropTileState {
    Vec2i tile;
    std::string cropId;
    bool planted = false;
    bool wateredToday = false;
    bool harvestReady = false;
    std::int32_t growthDays = 0;
    std::int32_t requiredGrowthDays = 0;
};

struct WorldItemEntity {
    std::uint64_t entityId = 0;
    ItemStack stack;
    Vec2i tile;
    bool persistent = true;
    double lifetimeSeconds = -1.0;
};

struct WorldClockState {
    std::int64_t dayNumber = 1;
    std::int32_t minuteOfDay = 360;
    double timeScale = 1.0;
    bool paused = false;
};

struct InventoryState {
    std::vector<ItemStack> slots;
};

struct WorldState {
    std::uint32_t saveVersion = 1;
    std::string saveName;
    WorldClockState clock;
    std::vector<CropTileState> crops;
    std::vector<WorldItemEntity> worldItems;
    InventoryState inventory;
};

} // namespace atlas
