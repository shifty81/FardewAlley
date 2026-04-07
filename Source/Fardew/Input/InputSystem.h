#pragma once

#include <unordered_map>
#include "Input/InputBindings.h"
#include "Input/InputState.h"

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
