#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "camera.h"
#include "player.h"
#include "renderer.h"
#include "world.h"

int main(void) {
    const int screenWidth = 1280;
    const int screenHeight = 720;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    SDL_Window *window = SDL_CreateWindow(
        "SDL2 + OpenGL FPS",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        screenWidth,
        screenHeight,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
    );

    if (!window) {
        fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        fprintf(stderr, "SDL_GL_CreateContext failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_GL_SetSwapInterval(1);
    SDL_SetRelativeMouseMode(SDL_TRUE);

    if (!renderer_init(screenWidth, screenHeight)) {
        fprintf(stderr, "renderer_init failed\n");
        SDL_GL_DeleteContext(glContext);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    World world;
    world_init(&world);

    Player player;
    player_init(&player, world.spawnPoint);

    Camera camera;
    camera_init(&camera, player.position);

    int running = 1;
    Uint64 prevCounter = SDL_GetPerformanceCounter();

    // FPS counter data
    Uint64 fpsTimer = SDL_GetPerformanceCounter();
    int fpsFrames = 0;

    while (running) {
        int mouseDx = 0;
        int mouseDy = 0;

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }

            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
                running = 0;
            }

            if (event.type == SDL_MOUSEMOTION) {
                mouseDx += event.motion.xrel;
                mouseDy += event.motion.yrel;
            }
        }

        Uint64 currentCounter = SDL_GetPerformanceCounter();
        float dt = (float)(currentCounter - prevCounter) / (float)SDL_GetPerformanceFrequency();
        prevCounter = currentCounter;

        if (dt > 0.033f) dt = 0.033f;

        const Uint8 *keys = SDL_GetKeyboardState(NULL);

        camera_update_mouse(&camera, mouseDx, mouseDy);
        player_update(&player, &camera, &world, keys, dt);
        camera_sync_to_player(&camera, player.position);

        renderer_begin_frame(screenWidth, screenHeight);
        renderer_draw_world(&camera, &world, screenWidth, screenHeight);
        renderer_draw_crosshair(screenWidth, screenHeight);
        renderer_end_frame(window);

        // FPS update once per second
        fpsFrames++;
        float fpsElapsed = (float)(currentCounter - fpsTimer) / (float)SDL_GetPerformanceFrequency();
        if (fpsElapsed >= 1.0f) {
            float fps = (float)fpsFrames / fpsElapsed;

            char title[128];
            snprintf(title, sizeof(title), "SDL2 + OpenGL FPS | FPS: %.0f", fps);
            SDL_SetWindowTitle(window, title);

            fpsFrames = 0;
            fpsTimer = currentCounter;
        }
    }

    renderer_shutdown();
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}