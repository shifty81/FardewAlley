cmake_minimum_required(VERSION 3.20)
project(ToolSystemPack_v1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(ToolSystemPack_v1 WIN32
    Source/Game/App/main.cpp
    Source/Game/Input/InputSystem.cpp
    Source/Game/Movement/MovementSystem.cpp
    Source/Game/Player/PlayerController.cpp
    Source/Game/Tools/ToolRegistry.cpp
    Source/Game/Tools/ToolRules.cpp
    Source/Game/Tools/ToolSystem.cpp
    Source/Game/World/TileMap.cpp
)

target_include_directories(ToolSystemPack_v1 PRIVATE Source)

target_compile_definitions(ToolSystemPack_v1 PRIVATE UNICODE _UNICODE)

if (MSVC)
    target_compile_options(ToolSystemPack_v1 PRIVATE /W4 /permissive-)
else()
    target_compile_options(ToolSystemPack_v1 PRIVATE -Wall -Wextra -Wpedantic)
endif()
