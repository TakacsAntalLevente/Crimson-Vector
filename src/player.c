#include "player.h"
#include <math.h>

static Vector3 NormalizeSafe(Vector3 v)
{
    float len = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
    if (len <= 0.0001f) return (Vector3){0.0f, 0.0f, 0.0f};
    return (Vector3){v.x / len, v.y / len, v.z / len};
}

BoundingBox Player_GetBoundingBoxAt(const Player *player, Vector3 position)
{
    BoundingBox box;
    box.min = (Vector3){
        position.x - player->radius,
        position.y,
        position.z - player->radius
    };
    box.max = (Vector3){
        position.x + player->radius,
        position.y + player->height,
        position.z + player->radius
    };
    return box;
}

void Player_Init(Player *player, Vector3 spawnPosition)
{
    player->position = spawnPosition;
    player->radius = 0.35f;
    player->height = 1.8f;
    player->moveSpeed = 5.0f;
    player->sprintMultiplier = 1.6f;
    player->jumpSpeed = 9.0f;
    player->gravity = -18.0f;
    player->verticalVelocity = 0.0f;
    player->onGround = 1;
}

void Player_Update(Player *player, const CameraController *camera, const World *world, float dt)
{
    Vector3 moveDir = {0.0f, 0.0f, 0.0f};
    Vector3 forward = CameraController_GetForwardFlat(camera);
    Vector3 right = CameraController_GetRightFlat(camera);

    if (IsKeyDown(KEY_W)) {
        moveDir.x += forward.x;
        moveDir.z += forward.z;
    }
    if (IsKeyDown(KEY_S)) {
        moveDir.x -= forward.x;
        moveDir.z -= forward.z;
    }
    if (IsKeyDown(KEY_D)) {
        moveDir.x -= right.x;
        moveDir.z -= right.z;
    }
    if (IsKeyDown(KEY_A)) {
        moveDir.x += right.x;
        moveDir.z += right.z;
    }

    moveDir = NormalizeSafe(moveDir);

    float currentSpeed = player->moveSpeed;
    if (IsKeyDown(KEY_LEFT_SHIFT)) {
        currentSpeed *= player->sprintMultiplier;
    }

    // X movement
    Vector3 desiredPosition = player->position;
    desiredPosition.x += moveDir.x * currentSpeed * dt;

    BoundingBox boxX = Player_GetBoundingBoxAt(player, desiredPosition);
    if (!World_CheckCollision(world, boxX)) {
        player->position.x = desiredPosition.x;
    }

    // Z movement
    desiredPosition = player->position;
    desiredPosition.z += moveDir.z * currentSpeed * dt;

    BoundingBox boxZ = Player_GetBoundingBoxAt(player, desiredPosition);
    if (!World_CheckCollision(world, boxZ)) {
        player->position.z = desiredPosition.z;
    }

    // Jump
    if (player->onGround && IsKeyPressed(KEY_SPACE)) {
        player->verticalVelocity = player->jumpSpeed;
        player->onGround = 0;
    }

    // Gravity
    player->verticalVelocity += player->gravity * dt;

    // Y movement
    float oldY = player->position.y;
    desiredPosition = player->position;
    desiredPosition.y += player->verticalVelocity * dt;

    BoundingBox yBox = Player_GetBoundingBoxAt(player, desiredPosition);

    player->onGround = 0;

    // Floor collision
    if (desiredPosition.y <= 0.0f) {
        player->position.y = 0.0f;
        player->verticalVelocity = 0.0f;
        player->onGround = 1;
        return;
    }

    // Box collision on Y
    int collidedY = 0;
    for (int i = 0; i < world->boxCount; ++i) {
        const BoundingBox box = world->boxes[i].bounds;

        if (CheckCollisionBoxes(yBox, box)) {
            float oldBottom = oldY;
            float oldTop = oldY + player->height;
            float newBottom = desiredPosition.y;
            float newTop = desiredPosition.y + player->height;

            // Landing on top of the box while falling
            if (player->verticalVelocity <= 0.0f && oldBottom >= box.max.y - 0.05f) {
                player->position.y = box.max.y + 0.02f;
                player->verticalVelocity = 0.0f;
                player->onGround = 1;
                collidedY = 2;
                break;
            }

            // Hitting the underside of the box while jumping
            if (player->verticalVelocity > 0.0f && oldTop <= box.min.y + 0.05f) {
                player->position.y = box.min.y - player->height;
                player->verticalVelocity = 0.0f;
                collidedY = 2;
                break;
            }
        }
    }

    if (!collidedY) {
        player->position.y = desiredPosition.y;
    }
}