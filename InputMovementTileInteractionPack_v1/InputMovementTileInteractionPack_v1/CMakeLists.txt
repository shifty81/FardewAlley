cmake_minimum_required(VERSION 3.20)
project(InputMovementTileInteractionPack_v1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(InputMovementTileInteractionPack_v1 WIN32
    Source/Game/App/main.cpp
    Source/Game/Input/InputSystem.cpp
    Source/Game/Movement/MovementSystem.cpp
    Source/Game/Interaction/InteractionSystem.cpp
    Source/Game/Player/PlayerController.cpp
    Source/Game/World/TileMap.cpp
)

target_include_directories(InputMovementTileInteractionPack_v1 PRIVATE Source)

target_compile_definitions(InputMovementTileInteractionPack_v1 PRIVATE UNICODE _UNICODE)

if (MSVC)
    target_compile_options(InputMovementTileInteractionPack_v1 PRIVATE /W4 /permissive-)
else()
    target_compile_options(InputMovementTileInteractionPack_v1 PRIVATE -Wall -Wextra -Wpedantic)
endif()
