cmake_minimum_required(VERSION 3.16)
project(crimsonvector C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(crimsonvector
    src/main.c
    src/camera.c
    src/player.c
    src/world.c
    src/renderer.c
)

target_include_directories(crimsonvector PRIVATE
    ${SDL2_INCLUDE_DIRS}
    src
)

target_link_libraries(crimsonvector PRIVATE ${SDL2_LIBRARIES} OpenGL::GL m)