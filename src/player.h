#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include "camera.h"
#include "world.h"

typedef struct Player {
    Vec3 position;
    float radius;
    float height;
    float moveSpeed;
    float sprintMultiplier;
    float jumpSpeed;
    float gravity;
    float verticalVelocity;
    int onGround;
    float runTime;
    int runActive;
    int finished;
} Player;

void player_init(Player *player, Vec3 spawnPosition);
AABB player_get_aabb_at(const Player *player, Vec3 position);
void player_update(Player *player, const Camera *camera, const World *world, const Uint8 *keys, float dt);

#endif