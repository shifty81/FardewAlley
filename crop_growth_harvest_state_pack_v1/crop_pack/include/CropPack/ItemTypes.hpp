#pragma once

#include <cstdint>
#include <string>

namespace CropPack {

enum class ItemId : std::uint32_t {
    None = 0,
    Parsnip,
    ParsnipSeed,
    Potato,
    PotatoSeed,
    Fiber,
    MixedSeed
};

inline std::string ToString(const ItemId itemId) {
    switch (itemId) {
        case ItemId::None: return "None";
        case ItemId::Parsnip: return "Parsnip";
        case ItemId::ParsnipSeed: return "ParsnipSeed";
        case ItemId::Potato: return "Potato";
        case ItemId::PotatoSeed: return "PotatoSeed";
        case ItemId::Fiber: return "Fiber";
        case ItemId::MixedSeed: return "MixedSeed";
        default: return "Unknown";
    }
}

} // namespace CropPack
