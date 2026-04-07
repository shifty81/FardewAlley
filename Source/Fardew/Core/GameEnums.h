#pragma once

namespace atlas
{
    enum class GameMode
    {
        Boot,
        MainMenu,
        InGame,
        Paused,
        ShuttingDown
    };

    enum class SessionMode
    {
        SinglePlayer,
        LocalCoop2P
    };

    enum class SplitMode
    {
        None,
        FixedVertical
    };

    enum class InputMode
    {
        Gameplay,
        UI,
        Dialogue,
        Menu
    };

    enum class PauseScope
    {
        None,
        LocalOnly,
        Global
    };

    enum class Direction
    {
        Down,
        Left,
        Right,
        Up
    };

    enum class PlayerAnimState
    {
        Idle,
        Walk,
        UseTool,
        Attack,
        Hurt,
        Downed
    };

    enum class ZoneTransitionType
    {
        Door,
        Ladder,
        EdgeWarp,
        Scripted,
        SleepReturn,
        Teleport
    };

    enum class TransitionRequirement
    {
        LocalOnly,
        AllPlayersReady
    };

    enum class InteractionType
    {
        None,
        Dialogue,
        Chest,
        Shop,
        Crafting,
        Bed,
        Door,
        Harvest,
        ToolTarget
    };
}
