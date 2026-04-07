#pragma once

namespace CropPack {

struct Int2 {
    int x = 0;
    int y = 0;

    constexpr bool operator==(const Int2& other) const noexcept {
        return x == other.x && y == other.y;
    }
};

struct Float2 {
    float x = 0.0f;
    float y = 0.0f;
};

} // namespace CropPack
