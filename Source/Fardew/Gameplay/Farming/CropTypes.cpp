#include "Gameplay/Farming/CropTypes.hpp"

namespace CropPack {

CropDatabase::CropDatabase() {
    CropTypeDef parsnip;
    parsnip.cropTypeId = CropTypeId::Parsnip;
    parsnip.seedItemId = ItemId::ParsnipSeed;
    parsnip.totalGrowthDays = 4;
    parsnip.regrows = false;
    parsnip.regrowDays = 0;
    parsnip.harvestDrops = {
        HarvestDropDef{ItemId::Parsnip, 1, 1, 1.0f},
        HarvestDropDef{ItemId::MixedSeed, 0, 1, 0.25f}
    };

    CropTypeDef potato;
    potato.cropTypeId = CropTypeId::Potato;
    potato.seedItemId = ItemId::PotatoSeed;
    potato.totalGrowthDays = 6;
    potato.regrows = false;
    potato.regrowDays = 0;
    potato.harvestDrops = {
        HarvestDropDef{ItemId::Potato, 1, 2, 1.0f},
        HarvestDropDef{ItemId::Fiber, 0, 1, 0.20f}
    };

    bySeed_.emplace(parsnip.seedItemId, parsnip.cropTypeId);
    bySeed_.emplace(potato.seedItemId, potato.cropTypeId);
    byCropType_.emplace(parsnip.cropTypeId, parsnip);
    byCropType_.emplace(potato.cropTypeId, potato);
}

const CropTypeDef* CropDatabase::FindByCropType(const CropTypeId cropTypeId) const {
    const auto it = byCropType_.find(cropTypeId);
    return it != byCropType_.end() ? &it->second : nullptr;
}

std::optional<CropTypeId> CropDatabase::FindBySeed(const ItemId seedItemId) const {
    const auto it = bySeed_.find(seedItemId);
    if (it == bySeed_.end()) {
        return std::nullopt;
    }
    return it->second;
}

} // namespace CropPack
