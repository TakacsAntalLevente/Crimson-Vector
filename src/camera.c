#include "camera.h"
#include <math.h>

static float clampf(float v, float minv, float maxv)
{
    if (v < minv) return minv;
    if (v > maxv) return maxv;
    return v;
}

void camera_init(Camera *camera, Vec3 playerPosition)
{
    camera->yaw = 0.0f;
    camera->pitch = 0.0f;
    camera->sensitivity = 0.0025f;
    camera->eyeHeight = 1.7f;
    camera->fovDegrees = 75.0f;

    camera->position = vec3(
        playerPosition.x,
        playerPosition.y + camera->eyeHeight,
        playerPosition.z
    );
}

void camera_update_mouse(Camera *camera, int mouseDx, int mouseDy)
{
    // Mouse movement -> rotation
    camera->yaw += (float)mouseDx * camera->sensitivity;
    camera->pitch -= (float)mouseDy * camera->sensitivity;

    // Clamp vertical look (prevents flipping)
    camera->pitch = clampf(camera->pitch, -1.5f, 1.5f);
}

void camera_sync_to_player(Camera *camera, Vec3 playerPosition)
{
    camera->position = vec3(
        playerPosition.x,
        playerPosition.y + camera->eyeHeight,
        playerPosition.z
    );
}

Vec3 camera_forward(const Camera *camera)
{
    float cp = cosf(camera->pitch);

    Vec3 forward = vec3(
        sinf(camera->yaw) * cp,
        sinf(camera->pitch),
        cosf(camera->yaw) * cp
    );

    return vec3_normalize(forward);
}

Vec3 camera_forward_flat(const Camera *camera)
{
    Vec3 forward = vec3(
        sinf(camera->yaw),
        0.0f,
        cosf(camera->yaw)
    );

    return vec3_normalize(forward);
}

Vec3 camera_right_flat(const Camera *camera)
{
    Vec3 forward = camera_forward_flat(camera);

    Vec3 right = vec3(
        forward.z,
        0.0f,
        -forward.x
    );

    return vec3_normalize(right);
}

Mat4 camera_view_matrix(const Camera *camera)
{
    Vec3 forward = camera_forward(camera);
    Vec3 target = vec3_add(camera->position, forward);

    return mat4_look_at(
        camera->position,
        target,
        vec3(0.0f, 1.0f, 0.0f)
    );
}