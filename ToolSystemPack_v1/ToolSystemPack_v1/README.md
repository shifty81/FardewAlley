# Tool System Pack v1

A minimal Win32 C++ starter pack that replaces hardcoded tile actions with an equipped-tool pipeline.

## Included

- keyboard input abstraction
- smooth tile movement
- equipped tool state
- tool registry
- tool rules
- tool system dispatch
- tile runtime state
- minimal Win32 loop
- debug output in the window title

## Controls

- W A S D: move
- Space: use equipped tool on facing tile
- Left Shift: sprint
- 1: equip axe
- 2: equip hoe
- 3: equip pickaxe
- 4: equip watering can
- Esc: quit

## Test Map

- Trees at `(1,1)` and `(6,1)`
- Rocks at `(3,2)` and `(0,0)`
- Water at `(4,4)` and `(5,4)`
- Everything else starts as grass or dirt with natural ground

Map legend in the title bar:

- `P` player
- `X` facing target tile
- `T` tree
- `R` rock
- `W` water
- `=` tilled soil
- `~` watered soil
- `G` grass
- `D` dirt

## Build

```powershell
cmake -S . -B build
cmake --build build --config Release
```

## Notes

- Rendering is intentionally omitted in v1.
- The watering can starts with `5/5` water for testing.
- World interaction is now routed through `FToolSystem::UseEquippedTool`.
- I could not verify a Windows build in this container because a Windows compiler toolchain is not available here.
