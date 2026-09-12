cmake_minimum_required(VERSION 3.20)

project(CustomGameEngineExercises LANGUAGES CXX)

add_executable(
    tank_state
    exercises/01-tank-state/main.cpp
)

target_compile_features(tank_state PRIVATE cxx_std_20)

set_target_properties(
    tank_state
    PROPERTIES
    CXX_EXTENSIONS OFF
)