#include "renderer.h"
#include <stdio.h>

static void set_matrix(const Mat4 *m) {
    glLoadMatrixf(m->m);
}

static void draw_cube(Vec3 pos, Vec3 size, Vec3 color) {
    float hx = size.x * 0.5f;
    float hy = size.y * 0.5f;
    float hz = size.z * 0.5f;

    glPushMatrix();
    glTranslatef(pos.x, pos.y, pos.z);
    glColor3f(color.x, color.y, color.z);

    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);
    glVertex3f(-hx, -hy, hz); glVertex3f(hx, -hy, hz); glVertex3f(hx, hy, hz); glVertex3f(-hx, hy, hz);
    glNormal3f(0, 0, -1);
    glVertex3f(hx, -hy, -hz); glVertex3f(-hx, -hy, -hz); glVertex3f(-hx, hy, -hz); glVertex3f(hx, hy, -hz);
    glNormal3f(-1, 0, 0);
    glVertex3f(-hx, -hy, -hz); glVertex3f(-hx, -hy, hz); glVertex3f(-hx, hy, hz); glVertex3f(-hx, hy, -hz);
    glNormal3f(1, 0, 0);
    glVertex3f(hx, -hy, hz); glVertex3f(hx, -hy, -hz); glVertex3f(hx, hy, -hz); glVertex3f(hx, hy, hz);
    glNormal3f(0, 1, 0);
    glVertex3f(-hx, hy, hz); glVertex3f(hx, hy, hz); glVertex3f(hx, hy, -hz); glVertex3f(-hx, hy, -hz);
    glNormal3f(0, -1, 0);
    glVertex3f(-hx, -hy, -hz); glVertex3f(hx, -hy, -hz); glVertex3f(hx, -hy, hz); glVertex3f(-hx, -hy, hz);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_QUADS);
    glVertex3f(-hx, -hy, hz); glVertex3f(hx, -hy, hz); glVertex3f(hx, hy, hz); glVertex3f(-hx, hy, hz);
    glVertex3f(hx, -hy, -hz); glVertex3f(-hx, -hy, -hz); glVertex3f(-hx, hy, -hz); glVertex3f(hx, hy, -hz);
    glVertex3f(-hx, -hy, -hz); glVertex3f(-hx, -hy, hz); glVertex3f(-hx, hy, hz); glVertex3f(-hx, hy, -hz);
    glVertex3f(hx, -hy, hz); glVertex3f(hx, -hy, -hz); glVertex3f(hx, hy, -hz); glVertex3f(hx, hy, hz);
    glVertex3f(-hx, hy, hz); glVertex3f(hx, hy, hz); glVertex3f(hx, hy, -hz); glVertex3f(-hx, hy, -hz);
    glVertex3f(-hx, -hy, -hz); glVertex3f(hx, -hy, -hz); glVertex3f(hx, -hy, hz); glVertex3f(-hx, -hy, hz);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glPopMatrix();
}

static void draw_floor(float size) {
    glColor3f(0.25f, 0.30f, 0.25f);
    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    glVertex3f(-size, 0.0f, -size);
    glVertex3f(size, 0.0f, -size);
    glVertex3f(size, 0.0f, size);
    glVertex3f(-size, 0.0f, size);
    glEnd();
}

int renderer_init(int width, int height) {
    (void)width;
    (void)height;

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat lightPos[] = { 4.0f, 8.0f, 4.0f, 1.0f };
    GLfloat lightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat lightAmbient[] = { 0.25f, 0.25f, 0.25f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);

    glClearColor(0.10f, 0.12f, 0.18f, 1.0f);
    return 1;
}

void renderer_shutdown(void) {
}

void renderer_begin_frame(int width, int height) {
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void renderer_draw_world(const Camera *camera, const World *world, int width, int height) {
    float aspect = (float)width / (float)height;
    Mat4 proj = mat4_perspective(camera->fovDegrees * (3.1415926535f / 180.0f), aspect, 0.1f, 100.0f);
    Mat4 view = camera_view_matrix(camera);

    glMatrixMode(GL_PROJECTION);
    set_matrix(&proj);

    glMatrixMode(GL_MODELVIEW);
    set_matrix(&view);

    draw_floor(20.0f);

    for (int i = 0; i < world->boxCount; ++i) {
        draw_cube(world->boxes[i].position, world->boxes[i].size, world->boxes[i].color);
    }
}

void renderer_draw_crosshair(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);

    int cx = width / 2;
    int cy = height / 2;
    int s = 8;

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex2i(cx - s, cy); glVertex2i(cx + s, cy);
    glVertex2i(cx, cy - s); glVertex2i(cx, cy + s);
    glEnd();

    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
}

void renderer_end_frame(SDL_Window *window) {
    SDL_GL_SwapWindow(window);
}