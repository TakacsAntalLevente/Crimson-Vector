#include "raylib.h"
#include "camera.h"
#include "player.h"
#include "renderer.h"
#include "world.h"

int main(void)
{
    const int screenWidth = 1280;
    const int screenHeight = 720;

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "Crimson Vector");
    SetTargetFPS(144);

    DisableCursor();

    World world;
    World_Init(&world);

    Player player;
    Player_Init(&player, world.spawnPoint);

    CameraController camera;
    CameraController_Init(&camera, player.position);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        if (IsKeyPressed(KEY_ESCAPE)) {
            if (IsCursorHidden()) EnableCursor();
            else DisableCursor();
        }

        if (IsCursorHidden()) {
            Player_Update(&player, &camera, &world, dt);
            CameraController_Update(&camera, player.position);
        } else {
            CameraController_Update(&camera, player.position);
        }

        Renderer_DrawFrame(&camera, &player, &world);
    }

    CloseWindow();
    return 0;
}