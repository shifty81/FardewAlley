#pragma once

#include <cstdint>
#include <vector>

#include "Gameplay/Farming/ItemTypes.hpp"
#include "Gameplay/Farming/MathTypes.hpp"

namespace CropPack {

struct WorldDropSpawnRequest {
    ItemId itemId = ItemId::None;
    int count = 0;
    Float2 worldPosition{};
    Float2 impulse{};
};

struct WorldItemEntity {
    std::uint64_t entityId = 0;
    ItemId itemId = ItemId::None;
    int count = 0;
    Float2 worldPosition{};
    Float2 impulse{};
};

class WorldDropSystem {
public:
    [[nodiscard]] std::vector<WorldItemEntity> Spawn(const std::vector<WorldDropSpawnRequest>& requests);

private:
    std::uint64_t nextEntityId_ = 1;
};

} // namespace CropPack
