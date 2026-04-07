# Day/Night + Time System Pack v1

Zip-ready C++20 starter pack for a simple deterministic world clock.

## Included
- `WorldClock` core runtime
- pause and time-scale support
- realtime tick and direct game-minute advance
- day rollover tracking
- day phase calculation
- schedule window checks
- daily event registration and trigger queue
- demo executable

## Build
```bash
cmake -S . -B build
cmake --build build
./build/day_night_time_demo
```

## Intended next integrations
- crop growth daily tick hookup
- station processing timers
- world item despawn timing
- sleep / skip-time flow
- save/load stamp serialization
