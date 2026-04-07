#pragma once

namespace Game
{
    enum class EActionResultType
    {
        None,
        Success,
        InvalidTarget,
        Blocked,
        OutOfRange,
        NotEnoughResource,
        NoToolEquipped
    };

    struct FActionResult
    {
        EActionResultType Type = EActionResultType::None;
        bool bChangedWorld = false;
        bool bConsumeTurn = false;
        bool bConsumeStamina = false;
    };
}
