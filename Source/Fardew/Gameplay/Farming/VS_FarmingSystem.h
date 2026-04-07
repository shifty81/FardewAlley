#pragma once

#include "Gameplay/Farming/VS_FarmingTypes.h"
#include <vector>

class FarmingSystem
{
public:
    void Resize(int width, int height);
    bool Till(int x, int y);
    bool Water(int x, int y);
    bool Plant(int x, int y, ItemType seedType, int daysToHarvest);
    bool Harvest(int x, int y, ItemType& outYield);
    void AdvanceDay();

    const FarmingTileState* TryGet(int x, int y) const;

private:
    bool InBounds(int x, int y) const;
    FarmingTileState& At(int x, int y);
    const FarmingTileState& At(int x, int y) const;

    int m_width = 0;
    int m_height = 0;
    std::vector<FarmingTileState> m_tiles;
};
