#include "Gameplay/Players/PlayerController.h"
#include <sstream>

namespace Game
{
    namespace
    {
        const wchar_t* FacingToString(EFacingDirection dir)
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
    }

    FPlayerController::FPlayerController(FTileMap& inTileMap)
        : TileMap(inTileMap)
        , MovementSystem(inTileMap)
    {
        Position.Tile = { 2, 2 };
        Position.World = { 2.0f, 2.0f };
    }

    void FPlayerController::HandleMovement(FInputSystem& input)
    {
        FTileCoord dir {};
        if (input.Get(EInputAction::MoveUp).bHeld) dir.Y -= 1;
        if (input.Get(EInputAction::MoveDown).bHeld) dir.Y += 1;
        if (input.Get(EInputAction::MoveLeft).bHeld) dir.X -= 1;
        if (input.Get(EInputAction::MoveRight).bHeld) dir.X += 1;

        bSprintHeld = input.Get(EInputAction::Sprint).bHeld;

        if (dir.X != 0 && dir.Y != 0)
        {
            dir.Y = 0;
        }

        MovementSystem.TryMove(Position, Movement, Facing, dir);
    }

    void FPlayerController::HandleInteraction(FInputSystem& input)
    {
        if (input.Get(EInputAction::Interact).bPressed)
        {
            LastInteractionMessage = InteractionSystem.TryInteract(Position, Facing, Interaction, TileMap);
        }
    }

    void FPlayerController::Update(float deltaTime, FInputSystem& input)
    {
        HandleMovement(input);
        HandleInteraction(input);
        MovementSystem.Update(deltaTime, Position, Movement, bSprintHeld);
    }

    std::wstring FPlayerController::BuildDebugStatus(const FTileMap& map) const
    {
        std::wstringstream ss;
        ss << L"Tile(" << Position.Tile.X << L"," << Position.Tile.Y << L") ";
        ss << L"Facing=" << FacingToString(Facing.Direction) << L" ";
        ss << L"Moving=" << (Movement.bIsMoving ? L"Yes" : L"No") << L" ";
        ss << L"| " << LastInteractionMessage << L" ";
        ss << L"| Map=" << map.BuildAsciiDebug(Position.Tile, Position.Tile);
        return ss.str();
    }
}
