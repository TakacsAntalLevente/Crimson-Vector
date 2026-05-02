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

    

    world->spawnPoint = vec3(0.0f, 3.0f, 0.0f);

    
    //parkour palya kezdes

    world_add_box(world, vec3(0, 0.5f, 0), vec3(4, 1, 4), vec3(0.2f, 0.8f, 0.2f));

    world_add_box(world, vec3(6, 1.0f, 0), vec3(2, 1, 2), vec3(0.2f, 0.4f, 0.8f));
    world_add_box(world, vec3(10, 1.5f, 0), vec3(2, 1, 2), vec3(0.2f, 0.4f, 0.8f));

    world_add_box(world, vec3(14, 2.0f, 2.5f), vec3(2, 1, 2), vec3(0.9f, 0.5f, 0.2f));

    world_add_box(world, vec3(18, 3.2f, 2.5f), vec3(3, 1, 3), vec3(0.8f, 0.2f, 0.2f));

    world_add_box(world, vec3(23, 4.5f, 2.5f), vec3(1.5f, 1, 1.5f), vec3(0.6f, 0.2f, 0.8f));
    world_add_box(world, vec3(27, 5.8f, 2.5f), vec3(1.5f, 1, 1.5f), vec3(0.6f, 0.2f, 0.8f));

    world_add_box(world, vec3(31, 7.0f, 5.0f), vec3(1.5f, 1, 1.5f), vec3(0.9f, 0.3f, 0.3f));

    world_add_box(world, vec3(36, 8.5f, 5.0f), vec3(5, 1, 5), vec3(0.9f, 0.8f, 0.2f));

    world->finishPoint = vec3(36, 8.5f, 5.0f);

    
}


int world_check_collision(const World *world, AABB playerBox) {
    for (int i = 0; i < world->boxCount; ++i) {
        if (aabb_intersects(playerBox, world->boxes[i].bounds)) {
            return 1;
        }
    }
    return 0;
}
