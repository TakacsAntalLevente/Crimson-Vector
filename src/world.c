#include "world.h"

static void world_add_box(World *world, Vec3 position, Vec3 size, Vec3 color) {
    if (world->boxCount >= MAX_WORLD_BOXES) return;

    WorldBox *box = &world->boxes[world->boxCount++];
    box->position = position;
    box->size = size;
    box->color = color;

    box->bounds.min = vec3(
        position.x - size.x * 0.5f,
        position.y - size.y * 0.5f,
        position.z - size.z * 0.5f
    );
    box->bounds.max = vec3(
        position.x + size.x * 0.5f,
        position.y + size.y * 0.5f,
        position.z + size.z * 0.5f
    );
}

void world_init(World *world) {
    world->boxCount = 0;
    world->arenaHalfSize = 12.0f;
    world->spawnPoint = vec3(0.0f, 0.0f, 0.0f);

    float s = world->arenaHalfSize;

    world_add_box(world, vec3(0.0f, 1.5f,  s), vec3(24.0f, 3.0f, 1.0f), vec3(0.55f, 0.55f, 0.55f));
    world_add_box(world, vec3(0.0f, 1.5f, -s), vec3(24.0f, 3.0f, 1.0f), vec3(0.55f, 0.55f, 0.55f));
    world_add_box(world, vec3( s, 1.5f, 0.0f), vec3(1.0f, 3.0f, 24.0f), vec3(0.55f, 0.55f, 0.55f));
    world_add_box(world, vec3(-s, 1.5f, 0.0f), vec3(1.0f, 3.0f, 24.0f), vec3(0.55f, 0.55f, 0.55f));

    world_add_box(world, vec3( 3.0f, 1.0f,  4.0f), vec3(2.0f, 2.0f, 2.0f), vec3(0.52f, 0.32f, 0.20f));
    world_add_box(world, vec3(-4.0f, 1.0f,  2.0f), vec3(2.5f, 2.0f, 2.5f), vec3(0.35f, 0.22f, 0.12f));
    world_add_box(world, vec3( 2.0f, 1.0f, -5.0f), vec3(3.0f, 2.0f, 2.0f), vec3(0.45f, 0.12f, 0.12f));
    world_add_box(world, vec3(-5.5f, 1.0f, -4.0f), vec3(2.0f, 2.0f, 3.0f), vec3(0.25f, 0.25f, 0.25f));
    world_add_box(world, vec3( 0.0f, 1.0f,  7.0f), vec3(4.0f, 2.0f, 1.5f), vec3(0.45f, 0.45f, 0.12f));
}

int world_check_collision(const World *world, AABB playerBox) {
    for (int i = 0; i < world->boxCount; ++i) {
        if (aabb_intersects(playerBox, world->boxes[i].bounds)) {
            return 1;
        }
    }
    return 0;
}