cmake_minimum_required(VERSION 3.16)
project(CrimsonVector)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
)

FetchContent_MakeAvailable(raylib)

add_executable(CrimsonVector
    src/main.c
    src/camera.c
    src/player.c
    src/world.c
    src/renderer.c
)

target_include_directories(CrimsonVector PRIVATE src)
target_link_libraries(CrimsonVector PRIVATE raylib)

if(APPLE)
    target_link_libraries(CrimsonVector PRIVATE
        "-framework IOKit"
        "-framework Cocoa"
        "-framework OpenGL"
    )
elseif(UNIX)
    target_link_libraries(CrimsonVector PRIVATE m pthread dl rt X11)
elseif(WIN32)
    target_link_libraries(CrimsonVector PRIVATE winmm gdi32)
endif()