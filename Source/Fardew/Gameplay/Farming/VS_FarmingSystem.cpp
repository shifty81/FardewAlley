#include "Gameplay/Farming/VS_FarmingSystem.h"

void FarmingSystem::Resize(int width, int height)
{
    m_width = width;
    m_height = height;
    m_tiles.assign(static_cast<size_t>(width * height), {});
}

bool FarmingSystem::InBounds(int x, int y) const
{
    return x >= 0 && y >= 0 && x < m_width && y < m_height;
}

FarmingTileState& FarmingSystem::At(int x, int y)
{
    return m_tiles[static_cast<size_t>(y * m_width + x)];
}

const FarmingTileState& FarmingSystem::At(int x, int y) const
{
    return m_tiles[static_cast<size_t>(y * m_width + x)];
}

const FarmingTileState* FarmingSystem::TryGet(int x, int y) const
{
    if (!InBounds(x, y))
        return nullptr;
    return &At(x, y);
}

bool FarmingSystem::Till(int x, int y)
{
    if (!InBounds(x, y))
        return false;
    auto& tile = At(x, y);
    tile.soil = SoilState::Tilled;
    return true;
}

bool FarmingSystem::Water(int x, int y)
{
    if (!InBounds(x, y))
        return false;
    auto& tile = At(x, y);
    if (tile.soil != SoilState::Tilled)
        return false;
    tile.wateredToday = true;
    return true;
}

bool FarmingSystem::Plant(int x, int y, ItemType seedType, int daysToHarvest)
{
    if (!InBounds(x, y))
        return false;
    auto& tile = At(x, y);
    if (tile.soil != SoilState::Tilled || tile.hasCrop)
        return false;

    tile.hasCrop = true;
    tile.cropSeedType = seedType;
    tile.growthDay = 0;
    tile.daysToHarvest = daysToHarvest;
    tile.harvestReady = false;
    return true;
}

bool FarmingSystem::Harvest(int x, int y, ItemType& outYield)
{
    if (!InBounds(x, y))
        return false;
    auto& tile = At(x, y);
    if (!tile.hasCrop || !tile.harvestReady)
        return false;

    outYield = (tile.cropSeedType == ItemType::SeedTurnip) ? ItemType::Turnip : ItemType::None;
    tile.hasCrop = false;
    tile.cropSeedType = ItemType::None;
    tile.growthDay = 0;
    tile.daysToHarvest = 0;
    tile.harvestReady = false;
    tile.wateredToday = false;
    return true;
}

void FarmingSystem::AdvanceDay()
{
    for (auto& tile : m_tiles)
    {
        if (tile.hasCrop && tile.wateredToday && !tile.harvestReady)
        {
            ++tile.growthDay;
            if (tile.growthDay >= tile.daysToHarvest)
                tile.harvestReady = true;
        }
        tile.wateredToday = false;
    }
}
