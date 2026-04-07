#pragma once

namespace Game
{
    enum class ETileType
    {
        Empty,
        Grass,
        Dirt,
        Water
    };

    enum class EGroundState
    {
        None,
        Natural,
        Tilled,
        Watered
    };
}
