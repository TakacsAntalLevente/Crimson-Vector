#ifndef CAMERA_H
#define CAMERA_H

#include "raylib.h"

typedef struct CameraController {
    Camera3D camera;
    float yaw;
    float pitch;
    float sensitivity;
    float eyeHeight;
} CameraController;

void CameraController_Init(CameraController *controller, Vector3 playerPosition);
void CameraController_Update(CameraController *controller, Vector3 playerPosition);
Vector3 CameraController_GetForward(const CameraController *controller);
Vector3 CameraController_GetForwardFlat(const CameraController *controller);
Vector3 CameraController_GetRightFlat(const CameraController *controller);

#endif