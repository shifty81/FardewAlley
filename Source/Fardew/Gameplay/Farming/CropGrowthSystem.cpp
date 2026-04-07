#include "Gameplay/Farming/CropGrowthSystem.hpp"

#include <algorithm>

namespace CropPack {

CropGrowthSystem::CropGrowthSystem(const CropDatabase& cropDatabase, const std::uint32_t seed)
    : cropDatabase_(cropDatabase), random_(seed) {}

void CropGrowthSystem::EnsureTile(const Int2& tile) {
    tiles_.try_emplace(tile, CropTileState{});
}

void CropGrowthSystem::TillTile(const Int2& tile) {
    auto& state = tiles_[tile];
    state.tilled = true;
}

void CropGrowthSystem::WaterTile(const Int2& tile) {
    auto& state = tiles_[tile];
    state.wateredToday = true;
}

PlantCropResult CropGrowthSystem::PlantCrop(const PlantCropRequest& request) {
    auto cropTypeId = cropDatabase_.FindBySeed(request.seedItemId);
    if (!cropTypeId.has_value()) {
        return {false, 0, "Seed item is not mapped to a crop type."};
    }

    auto& tileState = tiles_[request.tile];
    if (!tileState.tilled) {
        return {false, 0, "Tile is not tilled."};
    }

    if (tileState.occupied || cropsByTile_.find(request.tile) != cropsByTile_.end()) {
        return {false, 0, "Tile is already occupied by a crop."};
    }

    CropInstance crop;
    crop.cropEntityId = nextCropEntityId_++;
    crop.cropTypeId = *cropTypeId;
    crop.tile = request.tile;

    cropsByTile_[request.tile] = crop;
    tileState.occupied = true;
    return {true, crop.cropEntityId, ""};
}

void CropGrowthSystem::AdvanceDay() {
    for (auto& [tile, crop] : cropsByTile_) {
        auto tileIt = tiles_.find(tile);
        if (tileIt == tiles_.end()) {
            continue;
        }

        auto& tileState = tileIt->second;
        const CropTypeDef* cropDef = cropDatabase_.FindByCropType(crop.cropTypeId);
        if (cropDef == nullptr || crop.dead) {
            continue;
        }

        if (crop.readyToHarvest && cropDef->regrows) {
            if (tileState.wateredToday && crop.regrowCountdownDays > 0) {
                --crop.regrowCountdownDays;
            }
            if (crop.regrowCountdownDays <= 0) {
                crop.readyToHarvest = true;
                crop.mature = true;
            }
        } else {
            if (tileState.wateredToday) {
                ++crop.wateredDays;
                ++crop.ageDays;
            }
            if (crop.ageDays >= cropDef->totalGrowthDays) {
                crop.mature = true;
                crop.readyToHarvest = true;
            }
        }
    }

    for (auto& [tile, tileState] : tiles_) {
        tileState.wateredToday = false;
    }
}

HarvestResult CropGrowthSystem::HarvestAtTile(const Int2& tile) {
    const auto cropIt = cropsByTile_.find(tile);
    if (cropIt == cropsByTile_.end()) {
        return {false, {}, "No crop exists on this tile."};
    }

    CropInstance& crop = cropIt->second;
    const CropTypeDef* cropDef = cropDatabase_.FindByCropType(crop.cropTypeId);
    if (cropDef == nullptr) {
        return {false, {}, "Crop type definition is missing."};
    }

    if (!crop.readyToHarvest) {
        return {false, {}, "Crop is not ready to harvest."};
    }

    HarvestResult result;
    result.success = true;
    result.worldDrops = BuildHarvestDrops(crop, *cropDef);

    auto tileIt = tiles_.find(tile);
    if (cropDef->regrows) {
        crop.mature = false;
        crop.readyToHarvest = false;
        crop.regrowCountdownDays = cropDef->regrowDays;
    } else {
        if (tileIt != tiles_.end()) {
            tileIt->second.occupied = false;
        }
        cropsByTile_.erase(cropIt);
    }

    return result;
}

const CropInstance* CropGrowthSystem::FindCropAtTile(const Int2& tile) const {
    const auto it = cropsByTile_.find(tile);
    return it != cropsByTile_.end() ? &it->second : nullptr;
}

std::vector<CropInstance> CropGrowthSystem::GetAllCrops() const {
    std::vector<CropInstance> result;
    result.reserve(cropsByTile_.size());
    for (const auto& [tile, crop] : cropsByTile_) {
        (void)tile;
        result.push_back(crop);
    }
    return result;
}

std::size_t CropGrowthSystem::TileKeyHash::operator()(const Int2& value) const noexcept {
    const std::size_t xHash = std::hash<int>{}(value.x);
    const std::size_t yHash = std::hash<int>{}(value.y);
    return xHash ^ (yHash << 1U);
}

Float2 CropGrowthSystem::TileCenterToWorld(const Int2& tile) {
    return Float2{static_cast<float>(tile.x) + 0.5f, static_cast<float>(tile.y) + 0.5f};
}

std::vector<WorldDropSpawnRequest> CropGrowthSystem::BuildHarvestDrops(const CropInstance& crop, const CropTypeDef& cropDef) {
    std::vector<WorldDropSpawnRequest> drops;
    const Float2 center = TileCenterToWorld(crop.tile);

    std::uniform_real_distribution<float> chanceDistribution(0.0f, 1.0f);
    std::uniform_real_distribution<float> impulseDistribution(-0.35f, 0.35f);

    for (const HarvestDropDef& dropDef : cropDef.harvestDrops) {
        const float roll = chanceDistribution(random_);
        if (roll > dropDef.chance) {
            continue;
        }

        const int minCount = std::min(dropDef.minCount, dropDef.maxCount);
        const int maxCount = std::max(dropDef.minCount, dropDef.maxCount);
        std::uniform_int_distribution<int> countDistribution(minCount, maxCount);
        const int count = countDistribution(random_);
        if (count <= 0) {
            continue;
        }

        drops.push_back(WorldDropSpawnRequest{
            dropDef.itemId,
            count,
            center,
            Float2{impulseDistribution(random_), impulseDistribution(random_)}
        });
    }

    return drops;
}

} // namespace CropPack
