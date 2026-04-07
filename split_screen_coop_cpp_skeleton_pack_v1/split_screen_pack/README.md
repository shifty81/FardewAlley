# Split-Screen Co-op C++ Skeleton Pack v1

Native Windows oriented C++ skeleton for a 2-player top-down game with:
- fixed vertical split screen
- two local players
- shared world simulation
- independent cameras
- zone-aware player state
- local UI contexts
- shared save authority

This is a structure pack, not a finished engine.
It is intended as a direct starting point for Win32 + custom renderer, or Win32 + SDL2/OpenGL/D3D11.

## Included
- module skeletons
- core enums and structs
- session flow
- viewport logic
- update loop skeleton
- pause/menu policy enums
- zone transition contract
- TODO hooks for renderer, gameplay, and persistence

## Main implementation decisions
- 2 players max
- fixed vertical split in co-op
- one world simulation
- per-player cameras and HUD state
- one shared world save with per-player slots
- local menus do not globally pause by default

## Suggested next step
Wire these files into your real platform layer and renderer, then implement in this order:
1. one player and one camera
2. second player and second camera
3. split viewport rendering
4. zone transitions
5. interaction locks
6. save/load
