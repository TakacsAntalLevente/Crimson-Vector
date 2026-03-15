#include "renderer.h"
#include "raylib.h"
#include <stdio.h>

static void DrawCrosshair(void)
{
    int centerX = GetScreenWidth() / 2;
    int centerY = GetScreenHeight() / 2;
    int size = 8;

    DrawLine(centerX - size, centerY, centerX + size, centerY, WHITE);
    DrawLine(centerX, centerY - size, centerX, centerY + size, WHITE);
}

void Renderer_DrawFrame(const CameraController *camera, const Player *player, const World *world)
{
    (void)player;

    BeginDrawing();
    ClearBackground((Color){25, 30, 45, 255});

    BeginMode3D(camera->camera);

    DrawPlane((Vector3){0.0f, 0.0f, 0.0f}, (Vector2){40.0f, 40.0f}, (Color){60, 70, 60, 255});
    DrawGrid(40, 1.0f);

    for (int i = 0; i < world->boxCount; ++i) {
        const WorldBox *box = &world->boxes[i];
        DrawCubeV(box->position, box->size, box->color);
        DrawCubeWiresV(box->position, box->size, BLACK);
    }

    EndMode3D();

    DrawRectangle(10, 10, 220, 90, Fade(BLACK, 0.45f));
    DrawText("CrimsonVector", 20, 18, 20, RAYWHITE);
    DrawText("WASD: Move", 20, 44, 18, LIGHTGRAY);
    DrawText("Shift: Sprint   Space: Jump", 20, 64, 18, LIGHTGRAY);
    DrawFPS(20, 88);

    DrawCrosshair();

    EndDrawing();
}