cmake_minimum_required(VERSION 3.20)

project(CustomGameEngineExercises LANGUAGES CXX)

add_executable(
    tank_state
    exercises/01-tank-state/main.cpp
)

add_executable(
    tank_grid
    exercises/02-console-tank-grid/main.cpp
)

target_compile_features(tank_state PRIVATE cxx_std_20)
target_compile_features(tank_grid PRIVATE cxx_std_20)

set_target_properties(
    tank_state
    PROPERTIES
    CXX_EXTENSIONS OFF
)

set_target_properties(
    tank_grid
    PROPERTIES
    CXX_EXTENSIONS OFF
)