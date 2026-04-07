#pragma once

namespace Game
{
    enum class ETileType
    {
        Empty,
        Grass,
        Dirt,
        Water,
        Rock,
        Tree,
        TilledDirt,
        Stump
    };

    enum class EGroundState
    {
        None,
        Natural,
        Tilled,
        Watered
    };
}
