#pragma once

#include <cstdint>
#include <optional>
#include <random>
#include <unordered_map>
#include <vector>

#include "CropPack/CropTypes.hpp"
#include "CropPack/WorldDropSystem.hpp"

namespace CropPack {

struct PlantCropRequest {
    ItemId seedItemId = ItemId::None;
    Int2 tile{};
};

struct PlantCropResult {
    bool success = false;
    std::uint64_t cropEntityId = 0;
    const char* reason = "";
};

struct HarvestResult {
    bool success = false;
    std::vector<WorldDropSpawnRequest> worldDrops;
    const char* reason = "";
};

class CropGrowthSystem {
public:
    explicit CropGrowthSystem(const CropDatabase& cropDatabase, std::uint32_t seed = 1337U);

    void EnsureTile(const Int2& tile);
    void TillTile(const Int2& tile);
    void WaterTile(const Int2& tile);

    [[nodiscard]] PlantCropResult PlantCrop(const PlantCropRequest& request);
    void AdvanceDay();
    [[nodiscard]] HarvestResult HarvestAtTile(const Int2& tile);

    [[nodiscard]] const CropInstance* FindCropAtTile(const Int2& tile) const;
    [[nodiscard]] std::vector<CropInstance> GetAllCrops() const;

private:
    struct TileKeyHash {
        std::size_t operator()(const Int2& value) const noexcept;
    };

    [[nodiscard]] static Float2 TileCenterToWorld(const Int2& tile);
    [[nodiscard]] std::vector<WorldDropSpawnRequest> BuildHarvestDrops(const CropInstance& crop, const CropTypeDef& cropDef);

    const CropDatabase& cropDatabase_;
    std::mt19937 random_;
    std::unordered_map<Int2, CropTileState, TileKeyHash> tiles_;
    std::unordered_map<Int2, CropInstance, TileKeyHash> cropsByTile_;
    std::uint64_t nextCropEntityId_ = 1;
};

} // namespace CropPack
