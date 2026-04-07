#include "Game/Player/PlayerController.h"
#include <sstream>

namespace Game
{
    FPlayerController::FPlayerController(FTileMap& inTileMap)
        : TileMap(inTileMap)
        , MovementSystem(inTileMap)
    {
        Position.Tile = { 2, 2 };
        Position.World = { 2.0f, 2.0f };
        Tools.Equipped.Type = EToolType::Axe;
        Tools.Equipped.WaterMax = 5;
        Tools.Equipped.WaterCurrent = 5;
    }

    const wchar_t* FPlayerController::FacingToString(EFacingDirection dir)
    {
        switch (dir)
        {
            case EFacingDirection::Up: return L"Up";
            case EFacingDirection::Down: return L"Down";
            case EFacingDirection::Left: return L"Left";
            case EFacingDirection::Right: return L"Right";
            default: return L"Unknown";
        }
    }

    const wchar_t* FPlayerController::ToolToString(EToolType type)
    {
        switch (type)
        {
            case EToolType::Axe: return L"Axe";
            case EToolType::Hoe: return L"Hoe";
            case EToolType::Pickaxe: return L"Pickaxe";
            case EToolType::WateringCan: return L"WateringCan";
            default: return L"None";
        }
    }

    const wchar_t* FPlayerController::ResultToString(EActionResultType type)
    {
        switch (type)
        {
            case EActionResultType::Success: return L"Success";
            case EActionResultType::InvalidTarget: return L"InvalidTarget";
            case EActionResultType::Blocked: return L"Blocked";
            case EActionResultType::OutOfRange: return L"OutOfRange";
            case EActionResultType::NotEnoughResource: return L"NotEnoughResource";
            case EActionResultType::NoToolEquipped: return L"NoToolEquipped";
            default: return L"None";
        }
    }

    FTileCoord FPlayerController::GetFacingTargetTile(const FTileCoord& origin, EFacingDirection facing)
    {
        FTileCoord target = origin;
        switch (facing)
        {
            case EFacingDirection::Up: --target.Y; break;
            case EFacingDirection::Down: ++target.Y; break;
            case EFacingDirection::Left: --target.X; break;
            case EFacingDirection::Right: ++target.X; break;
        }
        return target;
    }

    void FPlayerController::HandleMovement(FInputSystem& input)
    {
        FTileCoord dir {};
        if (input.Get(EInputAction::MoveUp).bHeld) --dir.Y;
        if (input.Get(EInputAction::MoveDown).bHeld) ++dir.Y;
        if (input.Get(EInputAction::MoveLeft).bHeld) --dir.X;
        if (input.Get(EInputAction::MoveRight).bHeld) ++dir.X;

        bSprintHeld = input.Get(EInputAction::Sprint).bHeld;

        if (dir.X != 0 && dir.Y != 0)
        {
            dir.Y = 0;
        }

        MovementSystem.TryMove(Position, Movement, Facing, dir);
    }

    void FPlayerController::HandleToolEquip(FInputSystem& input)
    {
        if (input.Get(EInputAction::EquipAxe).bPressed)
        {
            Tools.Equipped.Type = EToolType::Axe;
            LastActionMessage = L"Equipped Axe";
        }
        else if (input.Get(EInputAction::EquipHoe).bPressed)
        {
            Tools.Equipped.Type = EToolType::Hoe;
            LastActionMessage = L"Equipped Hoe";
        }
        else if (input.Get(EInputAction::EquipPickaxe).bPressed)
        {
            Tools.Equipped.Type = EToolType::Pickaxe;
            LastActionMessage = L"Equipped Pickaxe";
        }
        else if (input.Get(EInputAction::EquipWateringCan).bPressed)
        {
            Tools.Equipped.Type = EToolType::WateringCan;
            LastActionMessage = L"Equipped Watering Can";
        }
    }

    void FPlayerController::HandleToolUse(FInputSystem& input)
    {
        if (!input.Get(EInputAction::UseTool).bPressed)
        {
            return;
        }

        FActionContext context {};
        context.ActorTile = Position.Tile;
        context.TargetTile = GetFacingTargetTile(Position.Tile, Facing.Direction);
        context.Facing = Facing.Direction;
        context.UseType = EToolUseType::PrimaryAction;

        const FActionResult result = ToolSystem.UseEquippedTool(Tools, context, TileMap);
        if (result.bConsumeStamina)
        {
            const FToolData* toolData = ToolSystem.GetToolData(Tools.Equipped.Type);
            if (toolData != nullptr)
            {
                Stamina.Current -= toolData->StaminaCost;
                if (Stamina.Current < 0)
                {
                    Stamina.Current = 0;
                }
            }
        }

        std::wstringstream ss;
        ss << L"Use " << ToolToString(Tools.Equipped.Type) << L" -> " << ResultToString(result.Type);
        LastActionMessage = ss.str();
    }

    void FPlayerController::Update(float deltaTime, FInputSystem& input)
    {
        HandleToolEquip(input);
        HandleMovement(input);
        HandleToolUse(input);
        MovementSystem.Update(deltaTime, Position, Movement, bSprintHeld);
    }

    std::wstring FPlayerController::BuildDebugStatus(const FTileMap& map) const
    {
        const FTileCoord target = GetFacingTargetTile(Position.Tile, Facing.Direction);
        std::wstringstream ss;
        ss << L"Tile(" << Position.Tile.X << L"," << Position.Tile.Y << L") ";
        ss << L"Facing=" << FacingToString(Facing.Direction) << L" ";
        ss << L"Tool=" << ToolToString(Tools.Equipped.Type) << L" ";
        ss << L"Water=" << Tools.Equipped.WaterCurrent << L"/" << Tools.Equipped.WaterMax << L" ";
        ss << L"Stamina=" << Stamina.Current << L"/" << Stamina.Max << L" ";
        ss << L"| " << LastActionMessage << L" ";
        ss << L"| Map=" << map.BuildAsciiDebug(Position.Tile, target);
        return ss.str();
    }
}
