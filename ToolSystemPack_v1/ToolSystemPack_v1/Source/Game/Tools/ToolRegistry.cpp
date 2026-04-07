#include "Game/Tools/ToolRegistry.h"

namespace Game
{
    const FToolData& FToolRegistry::Get(EToolType type)
    {
        static const FToolData None { EToolType::None, L"None", ETileActionAffinity::None, 0, 0.0f, 0, false };
        static const FToolData Axe { EToolType::Axe, L"Axe", ETileActionAffinity::Chop, 1, 1.0f, 2, false };
        static const FToolData Hoe { EToolType::Hoe, L"Hoe", ETileActionAffinity::Till, 1, 1.0f, 1, false };
        static const FToolData Pickaxe { EToolType::Pickaxe, L"Pickaxe", ETileActionAffinity::Mine, 1, 1.0f, 2, false };
        static const FToolData WateringCan { EToolType::WateringCan, L"Watering Can", ETileActionAffinity::Water, 1, 1.0f, 1, true };

        switch (type)
        {
            case EToolType::Axe: return Axe;
            case EToolType::Hoe: return Hoe;
            case EToolType::Pickaxe: return Pickaxe;
            case EToolType::WateringCan: return WateringCan;
            default: return None;
        }
    }
}
