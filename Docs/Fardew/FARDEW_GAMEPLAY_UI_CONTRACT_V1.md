# Fardew Alley Gameplay UI Contract v1

## Per-player HUD
Each local player should have:
- hotbar strip
- selected slot highlight
- stamina bar
- health bar
- held item or tool label
- context prompt label

## Split-screen layout rules
For the first pass:
- 1 player: full screen
- 2 players: horizontal split

## Input ownership rules
- each viewport only accepts gameplay input from its owning controller
- inventory screen is local to the owning player unless explicitly flagged shared
- shared modals block both players only when the modal affects shared world progression

## UI state model
Each player should own:
- hotbar selected slot
- inventory open state
- focused container id
- focused station id
- context prompt text id
