cmake_minimum_required(VERSION 3.16)
project(FardewAlley LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Collect all source files
file(GLOB_RECURSE FARDEW_SOURCES
    "Source/Fardew/*.cpp"
)

file(GLOB_RECURSE FARDEW_HEADERS
    "Source/Fardew/*.h"
    "Source/Fardew/*.hpp"
)

add_executable(fardew_alley ${FARDEW_SOURCES} ${FARDEW_HEADERS})

# SDL2 — required for window, rendering and input
find_package(SDL2 REQUIRED)

# Add Source/Fardew and all its subdirectories as include paths
target_include_directories(fardew_alley PRIVATE
    Source/Fardew
    Source/Fardew/Core
    Source/Fardew/Data
    Source/Fardew/Gameplay
    Source/Fardew/Gameplay/Dialogue
    Source/Fardew/Gameplay/Farming
    Source/Fardew/Gameplay/Interaction
    Source/Fardew/Gameplay/Inventory
    Source/Fardew/Gameplay/Players
    Source/Fardew/Gameplay/Session
    Source/Fardew/Input
    Source/Fardew/Movement
    Source/Fardew/Tools
    Source/Fardew/Time
    Source/Fardew/World
    Source/Fardew/World/TileMap
    Source/Fardew/World/Tilemap
    Source/Fardew/World/Zones
    Source/Fardew/Save
    Source/Fardew/Render
    Source/Fardew/UI
    Source/Fardew/Audio
    Source/Fardew/App
    Source/Fardew/Math
)

if(TARGET SDL2::SDL2)
    target_link_libraries(fardew_alley PRIVATE SDL2::SDL2)
else()
    target_include_directories(fardew_alley PRIVATE ${SDL2_INCLUDE_DIRS})
    target_link_libraries(fardew_alley PRIVATE ${SDL2_LIBRARIES})
endif()
