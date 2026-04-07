# Save/Load World Consolidation Pass v1

This starter pack consolidates the current vertical slice state into one simple save path:

- world clock
- crop tile states
- world-drop entities
- basic inventory contents

## Included

- `WorldTypes.hpp` for shared serialized state shapes
- `SaveLoad.hpp` with a text-based serializer/deserializer
- `main.cpp` demo that saves then reloads world state
- `CMakeLists.txt`

## Build

```bash
cmake -S . -B build
cmake --build build
./build/save_load_world_demo
```

## Why this pass matters

The previous packs created three different state families that now need one stable persistence path:

- crop growth and harvest state
- physical world item drops
- world time progression

This pass gives them one unified save boundary so later systems can plug into a single world snapshot contract.
