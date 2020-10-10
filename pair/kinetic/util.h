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
    /* +60º rotation */
    UP = 0,
    /* +0º rotation */
    HORIZONTAL,
    /* -60º rotation */
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
    struct Coordinate x0;
    struct Vector speed;
    /* root of cands tree of the point */
    struct CandsNode * candsRoot[3];
    /* node where the point is in a cands tree */
    struct CandsNode * cands[3];
    struct HitsNode * hitsLow[3];
    struct HitsNode * hitsUp[3];
    struct AVLNode * listPosition[3];
    struct Point * prev[3];
    struct Point * next[3];
    struct Cert * cert[4];
    int lastMatch[3];
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
    struct CandsNode * left;
    struct CandsNode * right;
    struct CandsNode * parent;
    struct Point * key;    
    /* points to the leftmost point in the node subtrees */
    struct CandsNode * leftmost;
} CandsNode;

typedef struct HitsNode
{
    struct HitsNode * left;
    struct HitsNode * right;
    struct HitsNode * parent;
    Point * key;
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

/* where points will be at first */
Point ** initial;

/* current time */
double now;

/* number of elements */
int n;

/* lastID available */
int lastID;

/* initializes things */
void init(int m);

void initialInsert(Point * p);

/* get p x-coordinate in the specified direction */
double getX(Point * p, int direction);

/* get p y-coordinate in the specified direction */
double getY(Point * p, int direction);

/* Calculates the distance between points a and b for direction direction*/
double distance(Point * a, Point * b, int direction);

/* returns cert type based on direction */
int certType(int direction);

/*
    Returns 1 if point c is to the left of the 
    parallel line to the x-axis that passes through point c rotated by theta (counterclockwise)
    0 if point c is in that line and -1 if point c is to the right of that line
*/
int checkLine(Point * a, Point * c, double theta);

#endif