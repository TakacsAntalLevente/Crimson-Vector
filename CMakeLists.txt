cmake_minimum_required(VERSION 3.16)
project(fps_sdl2_gl C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Find packages
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(fps_sdl2_gl
    src/main.c
    src/camera.c
    src/player.c
    src/world.c
    src/renderer.c
)

target_include_directories(fps_sdl2_gl PRIVATE src)

# Proper modern linking
target_link_libraries(fps_sdl2_gl PRIVATE
    mingw32
    SDL2main
    SDL2
    OpenGL::GL
)

# Only link math lib on Linux/macOS
if(NOT WIN32)
    target_link_libraries(fps_sdl2_gl PRIVATE m)
endif()