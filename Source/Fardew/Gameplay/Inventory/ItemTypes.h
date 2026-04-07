#pragma once

#include <string>

enum class ItemType
{
    None,
    Hoe,
    WateringCan,
    SeedTurnip,
    Turnip,
    Wood,
    Stone,
    SlimeGel,
    KeyItem
};

inline const char* ToString(ItemType type)
{
    switch (type)
    {
    case ItemType::Hoe: return "Hoe";
    case ItemType::WateringCan: return "Watering Can";
    case ItemType::SeedTurnip: return "Turnip Seeds";
    case ItemType::Turnip: return "Turnip";
    case ItemType::Wood: return "Wood";
    case ItemType::Stone: return "Stone";
    case ItemType::SlimeGel: return "Slime Gel";
    case ItemType::KeyItem: return "Key Item";
    default: return "None";
    }
}
