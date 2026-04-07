# Fardew Alley Foundation Consolidation Pass v1

This pack fills the highest-risk missing pieces in the current project:

- World model contract
- Tile schema
- Item and crop schemas
- Player state contract
- Interaction/action result framework
- Save schema
- Split-screen ownership rules
- Minimal gameplay UI contract

## Locked direction

- Native Windows C++
- Split-screen local co-op first
- LAN and join-by-IP later
- Top-down farming/adventure loop
- Vertical slice before large content expansion

## Folder intent

- `Source/Fardew/Core` shared primitive types and IDs
- `Source/Fardew/Data` data definitions and registries
- `Source/Fardew/Gameplay` runtime world, player, interaction, and co-op logic
- `Source/Fardew/Save` save schema and serialization helpers

## Missing pieces now defined

### 1. World model
The world is represented as tile chunks. Each chunk stores a fixed 2D tile grid. Dynamic entities are separate from tiles.

Core rules:
- Terrain lives on tiles
- Crops live on tiles
- Placeables can live on tiles
- Dropped items are dynamic entities
- Players are dynamic entities
- Interaction queries can inspect both tile content and nearby dynamic entities

### 2. Tile schema
Each tile has:
- terrain type
- flags
- moisture state
- crop instance id if occupied by crop
- placeable instance id if occupied by placeable

### 3. Item schema
All items use canonical integer IDs. Runtime code only references IDs and stack counts, not item names.

### 4. Crop schema
Crops are data-driven definitions with growth stage count, regrow rules, seasonal rules, and harvest output.

### 5. Player state
Player state is locked to:
- player id
- world position
- facing
- stamina and health
- selected hotbar slot
- inventory
- active interaction state
- split-screen ownership metadata

### 6. Interaction result framework
All actions return a common result object containing:
- success or failure
- action type
- stamina spent
- spawned drops
- tile changes
- message code

This prevents harvest, tool use, pickup, placement, and station interactions from becoming one-off code paths.

### 7. Save schema
The save root captures:
- metadata
- world clock
- players
- chunk tile state
- crops
- placeables
- dropped items

This is enough for the first real playable slice.

### 8. Split-screen rules
Current local co-op lock:
- max 2 players for first pass
- each player owns one viewport
- inventory is per-player
- money can be made shared later, but is kept out of this foundation pack
- pause/menu behavior should be host-owned in first pass
- day-end vote system deferred until sleep exists

### 9. Minimal gameplay UI contract
Defined but not fully rendered here:
- per-player hotbar
- per-player quick status panel
- shared modal ownership rules
- local inventory panel state

## Implementation strategy

1. Lock IDs and structs first
2. Route gameplay through common result objects
3. Save the same runtime state shape that gameplay actually uses
4. Keep the first pass deterministic and simple

## What this code pack intentionally does not solve yet

- Rendering
- Asset import pipeline
- NPC scheduling
- Shop economy
- Weather
- Full station queues
- Network replication

## Recommended next code pass after this pack

- Tool execution implementations for hoe, watering can, axe, and pickaxe
- Crop tick integration with day progression
- Inventory UI wiring
- Tilemap loading and rendering bridge
