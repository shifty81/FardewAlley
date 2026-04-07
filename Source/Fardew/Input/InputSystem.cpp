#include "Input/InputSystem.h"
#ifndef _WIN32
inline int GetAsyncKeyState(int) { return 0; }
#endif

namespace Game
{
    FInputSystem::FInputSystem()
        : Bindings(FInputBindings::CreateDefault())
    {
    }

    void FInputSystem::Update()
    {
        for (const auto& pair : Bindings.Keys)
        {
            const EInputAction action = pair.first;
            const int key = pair.second;
            FInputState& state = Current[action];

            const bool wasHeld = state.bHeld;
            const bool isHeld = (GetAsyncKeyState(key) & 0x8000) != 0;

            state.bHeld = isHeld;
            state.bPressed = !wasHeld && isHeld;
            state.bReleased = wasHeld && !isHeld;
        }
    }

    const FInputState& FInputSystem::Get(EInputAction action) const
    {
        static FInputState empty {};
        const auto it = Current.find(action);
        return it != Current.end() ? it->second : empty;
    }
}
