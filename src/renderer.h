#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "camera.h"
#include "world.h"

int renderer_init(int width, int height);
void renderer_shutdown(void);
void renderer_begin_frame(int width, int height);
void renderer_draw_world(const Camera *camera, const World *world, int width, int height);
void renderer_draw_crosshair(int width, int height);
void renderer_end_frame(SDL_Window *window);

#endif