#include <iostream>
#include <vector>

#include "CropPack/CropGrowthSystem.hpp"
#include "CropPack/CropTypes.hpp"
#include "CropPack/WorldDropSystem.hpp"

using namespace CropPack;

namespace {

void PrintCropState(const CropGrowthSystem& growthSystem, const Int2& tile) {
    const CropInstance* crop = growthSystem.FindCropAtTile(tile);
    if (crop == nullptr) {
        std::cout << "Tile (" << tile.x << ", " << tile.y << ") has no crop.\n";
        return;
    }

    std::cout
        << "Tile (" << tile.x << ", " << tile.y << ") cropEntity=" << crop->cropEntityId
        << " ageDays=" << crop->ageDays
        << " wateredDays=" << crop->wateredDays
        << " mature=" << (crop->mature ? "true" : "false")
        << " readyToHarvest=" << (crop->readyToHarvest ? "true" : "false")
        << "\n";
}

void PrintWorldDrops(const std::vector<WorldItemEntity>& drops) {
    for (const WorldItemEntity& drop : drops) {
        std::cout
            << "Spawned world drop entity=" << drop.entityId
            << " item=" << ToString(drop.itemId)
            << " count=" << drop.count
            << " pos=(" << drop.worldPosition.x << ", " << drop.worldPosition.y << ")"
            << " impulse=(" << drop.impulse.x << ", " << drop.impulse.y << ")"
            << "\n";
    }
}

} // namespace

int main() {
    CropDatabase cropDatabase;
    CropGrowthSystem growthSystem(cropDatabase, 42U);
    WorldDropSystem worldDropSystem;

    const Int2 farmTile{4, 7};
    growthSystem.EnsureTile(farmTile);
    growthSystem.TillTile(farmTile);

    const PlantCropResult plantResult = growthSystem.PlantCrop({ItemId::ParsnipSeed, farmTile});
    if (!plantResult.success) {
        std::cerr << "Plant failed: " << plantResult.reason << "\n";
        return 1;
    }

    std::cout << "Planted crop entity: " << plantResult.cropEntityId << "\n";

    for (int day = 1; day <= 4; ++day) {
        growthSystem.WaterTile(farmTile);
        growthSystem.AdvanceDay();
        std::cout << "After day " << day << ": ";
        PrintCropState(growthSystem, farmTile);
    }

    const HarvestResult harvestResult = growthSystem.HarvestAtTile(farmTile);
    if (!harvestResult.success) {
        std::cerr << "Harvest failed: " << harvestResult.reason << "\n";
        return 1;
    }

    const std::vector<WorldItemEntity> worldDrops = worldDropSystem.Spawn(harvestResult.worldDrops);
    PrintWorldDrops(worldDrops);
    PrintCropState(growthSystem, farmTile);

    return 0;
}
