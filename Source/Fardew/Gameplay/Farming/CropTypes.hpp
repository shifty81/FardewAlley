#pragma once

#include <cstdint>
#include <optional>
#include <unordered_map>
#include <vector>

#include "Gameplay/Farming/ItemTypes.hpp"
#include "Gameplay/Farming/MathTypes.hpp"

namespace CropPack {

enum class CropTypeId : std::uint32_t {
    None = 0,
    Parsnip,
    Potato
};

struct HarvestDropDef {
    ItemId itemId = ItemId::None;
    int minCount = 0;
    int maxCount = 0;
    float chance = 1.0f;
};

struct CropTypeDef {
    CropTypeId cropTypeId = CropTypeId::None;
    ItemId seedItemId = ItemId::None;
    int totalGrowthDays = 0;
    bool regrows = false;
    int regrowDays = 0;
    std::vector<HarvestDropDef> harvestDrops;
};

class CropDatabase {
public:
    CropDatabase();

    [[nodiscard]] const CropTypeDef* FindByCropType(CropTypeId cropTypeId) const;
    [[nodiscard]] std::optional<CropTypeId> FindBySeed(ItemId seedItemId) const;

private:
    std::unordered_map<CropTypeId, CropTypeDef> byCropType_;
    std::unordered_map<ItemId, CropTypeId> bySeed_;
};

struct CropTileState {
    bool tilled = false;
    bool wateredToday = false;
    bool occupied = false;
};

struct CropInstance {
    std::uint64_t cropEntityId = 0;
    CropTypeId cropTypeId = CropTypeId::None;
    Int2 tile{};
    int ageDays = 0;
    int wateredDays = 0;
    int regrowCountdownDays = 0;
    bool mature = false;
    bool readyToHarvest = false;
    bool dead = false;
};

} // namespace CropPack
