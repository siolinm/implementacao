#include<stdlib.h>
#include<math.h>
#ifndef _UTIL_H
#define _UTIL_H
#define INFINITE 100000000

#define PI_3 acos(0.5)

#define COS_PI_3 cos(PI_3)
#define SIN_PI_3 sin(PI_3)
#define SIN_NEG_PI_3 -SIN_PI_3 
#define COS_NEG_PI_3 COS_PI_3

#define EPS 0.000001

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
    /* +60-order event */
    UP_CERT = 0,
    /* 0-order event */
    HORIZONTAL_CERT,
    /* -60-order event */
    DOWN_CERT,
    /* kinetic tourn event */
    TOURN_CERT
};

enum Splay_types{
    CANDS_TREE = 0,
    HITS_UP_TREE,
    HITS_LOW_TREE
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
    char name; /* point's name */
    int id;
    Coordinate x0;
    Vector speed;
    struct Point * lcand[3];
    /* root of cands tree of the point */
    struct CandsNode * candsRoot[3];
    /* node where the point is in a cands tree */
    struct CandsNode * cands[3];
    /* node where the point is in a hitsLow tree */
    struct HitsNode * hitsLow[3];
    /* node where the point is in a hitsUp tree */
    struct HitsNode * hitsUp[3];
    struct HitsNode * hitsLowRoot[3];
    struct HitsNode * hitsUpRoot[3];
    struct AVLNode * listPosition[3];
    struct Point * prev[3];
    struct Point * next[3];
    Cert * cert[6];
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
    Point * key;
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

typedef Point Item;

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

/* get p x-coordinate in the specified direction */
double getX(Point * p, int direction);

/* get p y-coordinate in the specified direction */
double getY(Point * p, int direction);

/* get p x0-coordinate in the specified direction */
double getX0(Point * p, int direction);

/* get p y0-coordinate in the specified direction */
double getY0(Point * p, int direction);

/* get p speed first component in the specified direction */
double getVx(Point * p, int direction);

/* get p speed second component in the specified direction */
double getVy(Point * p, int direction);

/* Calculates the distance between points a and b for direction direction*/
double distance(Point * a, Point * b, int direction);

/* returns cert type based on direction */
int certType(int direction);

/*
    Returns 1 if point c is to the left of the 
    parallel line to the x-axis that passes through point c rotated by theta (counterclockwise)
    0 if point c is in that line and -1 if point c is to the right of that line
*/
int checkLine(Point * a, Point * c, double theta, int dir);

Point * getLcand(Point * p);

void printPoint(Point * p, int dir);

void destroy();

#endif