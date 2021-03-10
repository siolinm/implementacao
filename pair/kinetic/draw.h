#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>
#include <cairo/cairo.h>
#include <cairo/cairo-xlib.h>
#include <math.h>
#include <time.h>
#include"util.h"
#include"kds.h"
#ifndef _DRAW_H
#define _DRAW_H

#define LINE_WIDTH 5
#define WIDTH 1600
#define HEIGHT 900
#define FONT_SIZE 20
#define INITIAL_SCALE 60.0
#define STEP 0.01
#define STEP10 10*STEP

#define A_KEY 0x61
#define B_KEY 0x62
#define C_KEY 0x63
#define D_KEY 0x64
#define J_KEY 0x6a
#define K_KEY 0x6b
#define L_KEY 0x6c
#define I_KEY 0x69
#define E_KEY 0x65
#define M_KEY 0x6d
#define N_KEY 0x6e
#define S_KEY 0x73
#define T_KEY 0x74
#define X_KEY 0x78
#define Z_KEY 0x7a
#define RIGHT_KEY 0xff53
#define LEFT_KEY 0xff51
#define UP_KEY 0xff52
#define DOWN_KEY 0xff54
#define ENTER_KEY 0xff0d
#define ESC_KEY 0xff1b

cairo_surface_t *sfc;
cairo_t *ctx;

int drawState;
int drawDebug;
double SCALE, translate, x_c, y_c;

typedef struct Color{
    double r, g, b;
} Color;

Color red, green, blue, black, white, yellow;

struct timespec ts;

cairo_surface_t *cairo_create_x11_surface(int x, int y);

void cairo_close_x11_surface(cairo_surface_t *sfc);

void drawCreate(int x, int y);

void drawInit();

void drawTime();

Coordinate drawEdge(Point *p, int dir, int edge);

void drawPoints(Point * sel, Point * sel2);

void drawPoint(Point * p, Color color);

void drawLine(Point * p, Point * q, Color color);

void drawEdges(int dir);

void drawNextEvent();

void drawTest();

void drawClosestPair();

void drawUp(Point * p, int dir, Color color);

void drawLow(Point * p, int dir, Color color);

void drawCands(Point * p, int dir, Color color);

int drawHandleXEvent(cairo_surface_t *sfc);

Vector getVector(int dir, int order);

void draw();

void drawTourn();

void drawEvent(Point * p, Point * q, Point * t, void * root, int type, int dir);

void drawPointsTree(void * root, int type, Color color);

#endif