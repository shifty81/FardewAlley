#pragma once

#include <string>
#include "Game/Input/InputSystem.h"
#include "Game/Interaction/InteractionSystem.h"
#include "Game/Movement/MovementSystem.h"

namespace Game
{
    class FPlayerController
    {
    public:
        explicit FPlayerController(FTileMap& inTileMap);

        void Update(float deltaTime, FInputSystem& input);
        const FGridPosition& GetPosition() const noexcept { return Position; }
        std::wstring BuildDebugStatus(const FTileMap& map) const;
        const std::wstring& GetLastInteractionMessage() const noexcept { return LastInteractionMessage; }

    private:
        void HandleMovement(FInputSystem& input);
        void HandleInteraction(FInputSystem& input);

        FTileMap& TileMap;
        FGridPosition Position {};
        FMovementComponent Movement {};
        FFacingComponent Facing {};
        FInteractionComponent Interaction {};
        FMovementSystem MovementSystem;
        FInteractionSystem InteractionSystem;
        bool bSprintHeld = false;
        std::wstring LastInteractionMessage = L"Ready";
    };
}
