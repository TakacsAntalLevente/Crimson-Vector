#ifndef RENDERER_H
#define RENDERER_H

#include "camera.h"
#include "player.h"
#include "world.h"

void Renderer_DrawFrame(const CameraController *camera, const Player *player, const World *world);

#endif