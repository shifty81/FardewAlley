#pragma once

#include <string>
#include "Game/Input/InputSystem.h"
#include "Game/Interaction/ActionContext.h"
#include "Game/Interaction/ActionResult.h"
#include "Game/Movement/MovementSystem.h"
#include "Game/Tools/ToolComponent.h"
#include "Game/Tools/ToolSystem.h"
#include "Game/World/TileMap.h"

namespace Game
{
    struct FStaminaComponent
    {
        int Current = 100;
        int Max = 100;
    };

    class FPlayerController
    {
    public:
        explicit FPlayerController(FTileMap& inTileMap);

        void Update(float deltaTime, FInputSystem& input);
        std::wstring BuildDebugStatus(const FTileMap& map) const;

    private:
        void HandleMovement(FInputSystem& input);
        void HandleToolEquip(FInputSystem& input);
        void HandleToolUse(FInputSystem& input);
        static FTileCoord GetFacingTargetTile(const FTileCoord& origin, EFacingDirection facing);
        static const wchar_t* FacingToString(EFacingDirection dir);
        static const wchar_t* ToolToString(EToolType type);
        static const wchar_t* ResultToString(EActionResultType type);

        FTileMap& TileMap;
        FGridPosition Position {};
        FMovementComponent Movement {};
        FFacingComponent Facing {};
        FToolComponent Tools {};
        FToolSystem ToolSystem {};
        FStaminaComponent Stamina {};
        FMovementSystem MovementSystem;
        std::wstring LastActionMessage = L"Ready";
        bool bSprintHeld = false;
    };
}
