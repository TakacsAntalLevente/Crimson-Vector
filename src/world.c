#include "world.h"

static void World_AddBox(World *world, Vector3 position, Vector3 size, Color color)
{
    if (world->boxCount >= MAX_WORLD_BOXES) return;

    WorldBox *box = &world->boxes[world->boxCount++];

    box->position = position;
    box->size = size;
    box->color = color;

    box->bounds.min = (Vector3){
        position.x - size.x * 0.5f,
        position.y - size.y * 0.5f,
        position.z - size.z * 0.5f
    };

    box->bounds.max = (Vector3){
        position.x + size.x * 0.5f,
        position.y + size.y * 0.5f,
        position.z + size.z * 0.5f
    };
}

void World_Init(World *world)
{
    world->boxCount = 0;
    world->arenaHalfSize = 12.0f;
    world->spawnPoint = (Vector3){0.0f, 0.0f, 0.0f};

    float s = world->arenaHalfSize;

    World_AddBox(world, (Vector3){ 0.0f, 1.5f,  s}, (Vector3){24.0f, 3.0f, 1.0f}, GRAY);
    World_AddBox(world, (Vector3){ 0.0f, 1.5f, -s}, (Vector3){24.0f, 3.0f, 1.0f}, GRAY);
    World_AddBox(world, (Vector3){ s, 1.5f,  0.0f}, (Vector3){1.0f, 3.0f, 24.0f}, GRAY);
    World_AddBox(world, (Vector3){-s, 1.5f,  0.0f}, (Vector3){1.0f, 3.0f, 24.0f}, GRAY);

    World_AddBox(world, (Vector3){ 3.0f, 1.0f,  4.0f}, (Vector3){2.0f, 2.0f, 2.0f}, BROWN);
    World_AddBox(world, (Vector3){-4.0f, 1.0f,  2.0f}, (Vector3){2.5f, 2.0f, 2.5f}, DARKBROWN);
    World_AddBox(world, (Vector3){ 2.0f, 1.0f, -5.0f}, (Vector3){3.0f, 2.0f, 2.0f}, MAROON);
    World_AddBox(world, (Vector3){-5.5f, 1.0f, -4.0f}, (Vector3){2.0f, 2.0f, 3.0f}, DARKGRAY);
    World_AddBox(world, (Vector3){ 0.0f, 1.0f,  7.0f}, (Vector3){4.0f, 2.0f, 1.5f}, RED);
}

int World_CheckCollision(const World *world, BoundingBox playerBox)
{
    for (int i = 0; i < world->boxCount; ++i) {
        if (CheckCollisionBoxes(playerBox, world->boxes[i].bounds)) {
            return 1;
        }
    }
    return 0;
}