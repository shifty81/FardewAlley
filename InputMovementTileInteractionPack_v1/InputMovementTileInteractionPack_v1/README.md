# Input + Movement + Tile Interaction Pack v1

A minimal Win32 C++ starter pack for a Stardew-like vertical slice.

## Features

- Hardcoded keyboard input abstraction
- Tile-based smooth movement
- Player facing direction
- Tile blocking and interaction
- Minimal Win32 loop
- Debug text written to the window title

## Default Controls

- W A S D: Move
- E: Interact
- Left Shift: Sprint
- Esc: Quit

## Build

### Visual Studio / CMake

```powershell
cmake -S . -B build
cmake --build build --config Release
```

The executable will be created in the build output folder.

## Notes

- Rendering is intentionally omitted in v1.
- Interaction results are surfaced through the window title.
- This pack is designed to be easy to drop into a repo and extend.
