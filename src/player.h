#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "camera.h"
#include "world.h"

typedef struct Player {
    Vector3 position;
    float radius;
    float height;
    float moveSpeed;
    float sprintMultiplier;
    float jumpSpeed;
    float gravity;
    float verticalVelocity;
    int onGround;
} Player;

void Player_Init(Player *player, Vector3 spawnPosition);
void Player_Update(Player *player, const CameraController *camera, const World *world, float dt);
BoundingBox Player_GetBoundingBoxAt(const Player *player, Vector3 position);

#endif