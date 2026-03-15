#include "camera.h"
#include <math.h>

#ifndef PI
#define PI 3.14159265358979323846f
#endif

static float ClampFloat(float value, float minValue, float maxValue)
{
    if (value < minValue) return minValue;
    if (value > maxValue) return maxValue;
    return value;
}

static Vector3 NormalizeSafe(Vector3 v)
{
    float len = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
    if (len <= 0.0001f) return (Vector3){0.0f, 0.0f, 0.0f};
    return (Vector3){v.x / len, v.y / len, v.z / len};
}

void CameraController_Init(CameraController *controller, Vector3 playerPosition)
{
    controller->yaw = 0.0f;
    controller->pitch = 0.0f;
    controller->sensitivity = 0.0025f;
    controller->eyeHeight = 1.7f;

    controller->camera.position = (Vector3){
        playerPosition.x,
        playerPosition.y + controller->eyeHeight,
        playerPosition.z
    };

    controller->camera.target = (Vector3){
        controller->camera.position.x,
        controller->camera.position.y,
        controller->camera.position.z + 1.0f
    };

    controller->camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    controller->camera.fovy = 75.0f;
    controller->camera.projection = CAMERA_PERSPECTIVE;
}

Vector3 CameraController_GetForward(const CameraController *controller)
{
    float cp = cosf(controller->pitch);

    Vector3 forward = {
        sinf(controller->yaw) * cp,
        sinf(controller->pitch),
        cosf(controller->yaw) * cp
    };

    return NormalizeSafe(forward);
}

Vector3 CameraController_GetForwardFlat(const CameraController *controller)
{
    Vector3 forward = {
        sinf(controller->yaw),
        0.0f,
        cosf(controller->yaw)
    };

    return NormalizeSafe(forward);
}

Vector3 CameraController_GetRightFlat(const CameraController *controller)
{
    Vector3 forward = CameraController_GetForwardFlat(controller);

    Vector3 right = {
        forward.z,
        0.0f,
        -forward.x
    };

    return NormalizeSafe(right);
}

void CameraController_Update(CameraController *controller, Vector3 playerPosition)
{
    Vector2 mouseDelta = GetMouseDelta();

    controller->yaw += mouseDelta.x * controller->sensitivity;
    controller->pitch -= mouseDelta.y * controller->sensitivity;

    controller->pitch = ClampFloat(controller->pitch, -1.5f, 1.5f);

    controller->camera.position = (Vector3){
        playerPosition.x,
        playerPosition.y + controller->eyeHeight,
        playerPosition.z
    };

    Vector3 forward = CameraController_GetForward(controller);

    controller->camera.target = (Vector3){
        controller->camera.position.x + forward.x,
        controller->camera.position.y + forward.y,
        controller->camera.position.z + forward.z
    };
}