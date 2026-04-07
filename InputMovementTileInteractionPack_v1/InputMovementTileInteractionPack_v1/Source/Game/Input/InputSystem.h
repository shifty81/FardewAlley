#pragma once

#include <unordered_map>
#include "Game/Input/InputBindings.h"
#include "Game/Input/InputState.h"

namespace Game
{
    class FInputSystem
    {
    public:
        FInputSystem();

        void Update();
        const FInputState& Get(EInputAction action) const;

    private:
        FInputBindings Bindings;
        std::unordered_map<EInputAction, FInputState> Current;
    };
}
