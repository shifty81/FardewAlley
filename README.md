# Fardew Alley

A top-down farming/adventure game in C++17 with split-screen local co-op support.

## Building

### Linux / macOS (CMake)

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
make -j$(nproc)
./fardew_alley
```

Install SDL2 first if needed:
- **Ubuntu/Debian:** `sudo apt install libsdl2-dev`
- **macOS (Homebrew):** `brew install sdl2`

### Windows (Visual Studio)

1. Download the SDL2 **development libraries** for Windows (VC) from https://github.com/libsdl-org/SDL/releases and extract them (e.g. to `C:\SDL2`).
2. Set the environment variable `SDL2_DIR` to the root of the extracted folder (replace `2.x.x` with the actual version number you downloaded, e.g. `2.30.0`):
   ```
   setx SDL2_DIR "C:\SDL2\SDL2-2.x.x"
   ```
   The folder must contain `include\SDL2\SDL.h` and `lib\x64\SDL2.lib`.
3. Restart Visual Studio, then open `FardewAlley.sln` and build normally.
4. Copy `$(SDL2_DIR)\lib\x64\SDL2.dll` next to the built `.exe` before running.

## Project Structure

All game source code lives under `Source/Fardew/`:

```
Source/Fardew/
├── App/            # GameApp entry point and main loop
├── Audio/          # Audio system (stereo listener for split-screen)
├── Core/           # Shared types, enums, math primitives, tile definitions
├── Data/           # Item and crop data registries
├── Gameplay/
│   ├── Dialogue/   # Dialogue system for NPCs
│   ├── Farming/    # Crop growth, harvest, world drops
│   ├── Interaction/# Chest, tile interaction, vertical-slice interaction
│   ├── Inventory/  # Slot-based inventory with stacking
│   ├── Players/    # Player state, controller, manager
│   └── Session/    # Session management, split-screen system
├── Input/          # Input polling, bindings, state
├── Math/           # Vec2, Rect utilities
├── Movement/       # Grid-based movement with smooth interpolation
├── Render/         # 2D renderer, camera, viewport management
├── Save/           # Save/load serialization, save types
├── Time/           # Day/night cycle, world clock
├── Tools/          # Tool registry, rules, stamina-based usage
├── UI/             # HUD renderer, UI manager
└── World/
    ├── TileMap/    # Tile storage, tile types and state
    ├── Tilemap/    # Tilemap loader, collision grid
    └── Zones/      # Zone streaming, transitions
```

## Assembled From

This project consolidates code from the following packs:
- **fardew_foundation_pack_v1** — Core types, data, gameplay, save schema
- **InputMovementTileInteractionPack_v1** — Input, movement, tile interaction
- **ToolSystemPack_v1** — Tool registry and usage system
- **crop_growth_harvest_state_pack_v1** — Crop growth and harvesting
- **day_night_time_system_pack_v1** — Day/night time cycle
- **save_load_world_consolidation_pass_v1** — Save/load consolidation
- **split_screen_coop_cpp_skeleton_pack_v1** — Split-screen local co-op
- **vertical_slice_gameplay_pack_v1** — Vertical slice gameplay demo

## Design Direction

- Native C++17
- Split-screen local co-op first (max 2 players)
- LAN and join-by-IP later
- Top-down farming/adventure loop
- Vertical slice before large content expansion