cmake_minimum_required(VERSION 3.20)
project(DayNightTimeSystemPackV1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(day_night_time_demo
    src/main.cpp
    src/TimeSystem.cpp
)

target_include_directories(day_night_time_demo PRIVATE include)
