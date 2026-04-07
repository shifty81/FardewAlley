#pragma once

#include <windows.h>
#include <unordered_map>
#include "Game/Input/InputAction.h"

namespace Game
{
    struct FInputBindings
    {
        std::unordered_map<EInputAction, int> Keys;

        static FInputBindings CreateDefault()
        {
            FInputBindings bindings;
            bindings.Keys[EInputAction::MoveUp] = 'W';
            bindings.Keys[EInputAction::MoveDown] = 'S';
            bindings.Keys[EInputAction::MoveLeft] = 'A';
            bindings.Keys[EInputAction::MoveRight] = 'D';
            bindings.Keys[EInputAction::UseTool] = VK_SPACE;
            bindings.Keys[EInputAction::Sprint] = VK_LSHIFT;
            bindings.Keys[EInputAction::Pause] = VK_ESCAPE;
            bindings.Keys[EInputAction::EquipAxe] = '1';
            bindings.Keys[EInputAction::EquipHoe] = '2';
            bindings.Keys[EInputAction::EquipPickaxe] = '3';
            bindings.Keys[EInputAction::EquipWateringCan] = '4';
            return bindings;
        }
    };
}
