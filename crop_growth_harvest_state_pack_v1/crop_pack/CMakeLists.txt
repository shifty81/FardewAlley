cmake_minimum_required(VERSION 3.20)
project(CropGrowthHarvestStatePackV1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(crop_growth_demo
    src/main.cpp
    src/CropTypes.cpp
    src/CropGrowthSystem.cpp
    src/WorldDropSystem.cpp
)

target_include_directories(crop_growth_demo PRIVATE include)

if (MSVC)
    target_compile_options(crop_growth_demo PRIVATE /W4 /permissive-)
else()
    target_compile_options(crop_growth_demo PRIVATE -Wall -Wextra -Wpedantic)
endif()
