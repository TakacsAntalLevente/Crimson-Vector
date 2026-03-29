#ifndef CAMERA_H
#define CAMERA_H

#include "math3d.h"

typedef struct Camera {
    Vec3 position;
    float yaw;
    float pitch;
    float sensitivity;
    float eyeHeight;
    float fovDegrees;
} Camera;

void camera_init(Camera *camera, Vec3 playerPosition);
void camera_update_mouse(Camera *camera, int mouseDx, int mouseDy);
void camera_sync_to_player(Camera *camera, Vec3 playerPosition);
Vec3 camera_forward(const Camera *camera);
Vec3 camera_forward_flat(const Camera *camera);
Vec3 camera_right_flat(const Camera *camera);
Mat4 camera_view_matrix(const Camera *camera);

#endif