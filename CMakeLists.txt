cmake_minimum_required(VERSION 3.16)

project(raycaster
    VERSION 1.0
    LANGUAGES C
)

# Generate compile_commands.json (for clangd / nvim)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Find SDL3
find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)

file(GLOB_RECURSE SOURCES
    src/main.c
    src/player.c
    src/map.c
    src/raycaster.c
    src/renderer.c
)

add_executable(raycaster ${SOURCES})

target_include_directories(raycaster PRIVATE
    src
)

target_link_libraries(raycaster PRIVATE SDL3::SDL3)

# Warnings (optional but recommended)
target_compile_options(raycaster PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

