#ifndef WORLD_H
#define WORLD_H

#include "raylib.h"

#define MAX_WORLD_BOXES 64

typedef struct WorldBox {
    Vector3 position;
    Vector3 size;
    Color color;
    BoundingBox bounds;
} WorldBox;

typedef struct World {
    WorldBox boxes[MAX_WORLD_BOXES];
    int boxCount;
    Vector3 spawnPoint;
    float arenaHalfSize;
} World;

void World_Init(World *world);
int World_CheckCollision(const World *world, BoundingBox playerBox);

#endif