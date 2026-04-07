#include "Gameplay/Farming/WorldDropSystem.hpp"

namespace CropPack {

std::vector<WorldItemEntity> WorldDropSystem::Spawn(const std::vector<WorldDropSpawnRequest>& requests) {
    std::vector<WorldItemEntity> result;
    result.reserve(requests.size());

    for (const WorldDropSpawnRequest& request : requests) {
        result.push_back(WorldItemEntity{
            nextEntityId_++,
            request.itemId,
            request.count,
            request.worldPosition,
            request.impulse
        });
    }

    return result;
}

} // namespace CropPack
