#include<stdlib.h>
#include<math.h>
#ifndef _UTIL_H
#define _UTIL_H

#define PI_3 acos(0.5)

#define COS_PI_3 cos(PI_3)
#define SIN_PI_3 sin(PI_3)
#define SIN_NEG_PI_3 -SIN_PI_3 
#define COS_NEG_PI_3 COS_PI_3

enum Directions{
    UP = 0,
    HORIZONTAL,
    DOWN
};

/* TOURN_CERT + HORIZONTAL_CERT, TOURN_CERT + UP_CERT */
enum Cert_types{
    /* 0-order event */
    HORIZONTAL_CERT = 0,
    /* +60-order event */
    UP_CERT,
    /* -60-order event */
    DOWN_CERT,
    /* kinetic tourn event */
    TOURN_CERT
};

typedef struct Coordinate
{
    double x;
    double y;
} Coordinate;

typedef struct Vector
{
    double x;
    double y;
} Vector;

typedef struct Cert{
    /* certificate type */
    int pqpos;
    double value;
} Cert;

typedef struct Point{
    int id;
    Coordinate x0;
    Vector speed;
    CandsNode * cands[3];
    HitsNode * hitsLow[3];
    HitsNode * hitsUp[3];
    AVLNode * listPosition[3];
    Point * prev[3];
    Point * next[3];
    Cert * cert[4];
} Point;

typedef Point Object;

typedef struct AVLNode
{
    struct AVLNode * left;
    struct AVLNode * right;
    Object * key;
    int children;
    int height;
} AVLNode;

typedef struct CandsNode
{
    CandsNode * left;
    CandsNode * right;
    CandsNode * parent;
    /* points to the leftmost point in the node subtrees */
    CandsNode * leftmost;
} CandsNode;

typedef struct HitsNode
{
    HitsNode * left;
    HitsNode * right;
    HitsNode * parent;
} HitsNode;

typedef struct TournObject{
    Point * p;
    Point * lcandp;
    int direction;
} TournObject;

typedef struct PQObject{
    Point * p;
    int certType;
} PQObject;

/* priority queue */
PQObject ** Q;

/* kinetic tourn */
TournObject ** tourn;

/* current time */
double now;

/* initializes things */
void init();

/* get p x-coordinate in the specified direction */
double getX(Point * p, int direction);

/* get p y-coordinate in the specified direction */
double getY(Point * p, int direction);

/* returns cert type based on direction */
int certType(int direction);

#endif