#ifndef WORLD_H
#define WORLD_H

#include "math3d.h"

#define MAX_WORLD_BOXES 64

typedef struct WorldBox {
    Vec3 position;
    Vec3 size;
    Vec3 color;
    AABB bounds;
} WorldBox;

typedef struct World {
    WorldBox boxes[MAX_WORLD_BOXES];
    int boxCount;
    Vec3 spawnPoint;
    float arenaHalfSize;
} World;

void world_init(World *world);
int world_check_collision(const World *world, AABB playerBox);

#endif