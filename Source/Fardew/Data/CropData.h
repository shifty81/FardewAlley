#pragma once

#include "../Core/FardewTypes.h"
#include "ItemData.h"
#include <array>
#include <unordered_map>

namespace Fardew
{
    struct CropDefinition
    {
        CropId Id = 0;
        std::string Name;
        ItemId SeedItemId = 0;
        ItemId HarvestItemId = 0;
        std::array<std::uint8_t, 4> StageDays { 0, 0, 0, 0 };
        bool Regrows = false;
        std::uint8_t RegrowDays = 0;
        std::array<bool, 4> ValidSeasons { true, false, false, false };
    };

    struct CropInstance
    {
        EntityId InstanceId = 0;
        CropId DefinitionId = 0;
        Int2 Tile{};
        std::uint8_t StageIndex = 0;
        std::uint16_t DaysInStage = 0;
        bool WateredToday = false;
        bool HarvestReady = false;
    };

    class CropDatabase
    {
    public:
        void Register(const CropDefinition& definition);
        [[nodiscard]] const CropDefinition* Find(CropId id) const;
        [[nodiscard]] const CropDefinition* FindBySeed(ItemId itemId) const;

    private:
        std::unordered_map<CropId, CropDefinition> m_Definitions;
    };
}
