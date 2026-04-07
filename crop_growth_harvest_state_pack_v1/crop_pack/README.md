# Crop Growth + Harvest State Pack v1

This starter pack is a compact, compilable C++ baseline for a farming loop with harvest routed to world-drop output instead of direct inventory insertion.

## Included behavior

- tilled tile state
- watered-today tile state
- crop planting from seed item IDs
- per-day crop growth advancement
- mature and ready-to-harvest state tracking
- harvest output converted into world-drop spawn requests
- world-drop entity spawning pass
- deterministic demo using a fixed RNG seed

## Structure

- `include/CropPack/MathTypes.hpp`
- `include/CropPack/ItemTypes.hpp`
- `include/CropPack/CropTypes.hpp`
- `include/CropPack/CropGrowthSystem.hpp`
- `include/CropPack/WorldDropSystem.hpp`
- `src/CropTypes.cpp`
- `src/CropGrowthSystem.cpp`
- `src/WorldDropSystem.cpp`
- `src/main.cpp`
- `CMakeLists.txt`

## Build

### Windows with CMake

```powershell
cmake -S . -B build
cmake --build build --config Release
```

### Run

Executable output name:

- `crop_growth_demo`

## Integration intent

This pack is designed to plug into a larger game stack where:

- tile occupancy already exists or is being added
- crop defs move to data assets later
- world-drop spawn requests feed an existing pickup/drop system
- tool actions call `HarvestAtTile()` through a shared interaction pipeline

## Expected next integration pass

The clean follow-up is:

- tool system hook for hoe, water, and harvest actions
- save/load serialization for crop instances and tile moisture
- seasonal rules and crop death/failure conditions
- multiplayer authority and replication path
- sprite or render-state mapping for each growth stage
