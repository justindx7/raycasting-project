cmake_minimum_required(VERSION 3.16)

project(raycaster
    VERSION 1.0
    LANGUAGES C
)

# Generate compile_commands.json (for clangd / nvim)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Use modern C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Find SDL2 (Homebrew-compatible)
find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)

# Recursively collect source files (similar to find in Makefile)
file(GLOB_RECURSE SOURCES
    src/main.c
    src/player.c
    src/map.c
    src/raycaster.c
    src/renderer.c
)

# Create executable
add_executable(raycaster ${SOURCES})

# Include directories
target_include_directories(raycaster PRIVATE
    src
)

# Link SDL2
target_link_libraries(raycaster PRIVATE SDL3::SDL3)

# Warnings (optional but recommended)
target_compile_options(raycaster PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

