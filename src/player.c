#include "player.h"

AABB player_get_aabb_at(const Player *player, Vec3 position)
{
    AABB box;
    box.min = vec3(position.x - player->radius, position.y, position.z - player->radius);
    box.max = vec3(position.x + player->radius, position.y + player->height, position.z + player->radius);
    return box;
}

void player_init(Player *player, Vec3 spawnPosition)
{
    player->position = spawnPosition;
    player->radius = 0.35f;
    player->height = 1.8f;
    player->moveSpeed = 5.0f;
    player->sprintMultiplier = 1.6f;
    player->jumpSpeed = 12.0f;
    player->gravity = -18.0f;
    player->verticalVelocity = 0.0f;
    player->onGround = 1;
    player->runTime = 0.0f;
    player->runActive = 0;
    player->finished = 0;
}

void player_update(Player *player, const Camera *camera, const World *world, const Uint8 *keys, float dt)
{
    const float skin = 0.01f;

    Vec3 moveDir = vec3(0.0f, 0.0f, 0.0f);
    Vec3 forward = camera_forward_flat(camera);
    Vec3 right = camera_right_flat(camera);

    // --- INPUT ---
    if (keys[SDL_SCANCODE_W]) moveDir = vec3_add(moveDir, forward);
    if (keys[SDL_SCANCODE_S]) moveDir = vec3_sub(moveDir, forward);
    if (keys[SDL_SCANCODE_D]) moveDir = vec3_add(moveDir, right);
    if (keys[SDL_SCANCODE_A]) moveDir = vec3_sub(moveDir, right);

    moveDir = vec3_normalize(moveDir);

    if (player->position.y < world->spawnPoint.y - 10.0f) {
    player->position = world->spawnPoint;

    player->verticalVelocity = 0.0f;
    player->onGround = 0;

    // IMPORTANT: reset Y movement properly
    return;
    }

    float speed = player->moveSpeed;
    if (keys[SDL_SCANCODE_LSHIFT]) speed *= player->sprintMultiplier;

    // --- X AXIS ---
    Vec3 desired = player->position;
    desired.x += moveDir.x * speed * dt;

    if (!world_check_collision(world, player_get_aabb_at(player, desired))) {
        player->position.x = desired.x;
    }

    // --- Z AXIS ---
    desired = player->position;
    desired.z += moveDir.z * speed * dt;

    if (!world_check_collision(world, player_get_aabb_at(player, desired))) {
        player->position.z = desired.z;
    }

    // --- JUMP ---
    if (player->onGround && keys[SDL_SCANCODE_SPACE]) {
        player->verticalVelocity = player->jumpSpeed;
        player->onGround = 0;
    }

    

    // --- GRAVITY ---
    float oldY = player->position.y;
    player->verticalVelocity += player->gravity * dt;

    desired = player->position;
    desired.y += player->verticalVelocity * dt;

    player->onGround = 1;

    
  
    // --- Y COLLISION (BOXES) ---
    AABB yBox = player_get_aabb_at(player, desired);
    int collidedY = 0;

    for (int i = 0; i < world->boxCount; ++i) {
        AABB box = world->boxes[i].bounds;

        if (!aabb_intersects(yBox, box)) continue;

        float oldBottom = oldY;
        float oldTop = oldY + player->height;

        // Landing on top
        if (player->verticalVelocity <= 0.0f && oldBottom >= box.max.y - 0.05f) {
            player->position.y = box.max.y + skin;
            player->verticalVelocity = 0.0f;
            player->onGround = 1;
            collidedY = 1;
            break;
        }

        // Hitting underside
        if (player->verticalVelocity > 0.0f && oldTop <= box.min.y + 0.05f) {
            player->position.y = box.min.y - player->height - skin;
            player->verticalVelocity = 0.0f;
            collidedY = 1;
            break;
        }
    }

    if (!collidedY) {
        player->position.y = desired.y;
    }

    // timer start
    if (!player->runActive) {
        player->runActive = 1;
    }

    // update timer
    if (player->runActive && !player->finished) {
        player->runTime += dt;
    }

    Vec3 diff = vec3_sub(player->position, world->finishPoint);
    float dist = vec3_length(diff);

    if (dist < 2.5f && !player->finished) {
        player->finished = 1;
    }
}