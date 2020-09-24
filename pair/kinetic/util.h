#ifndef _UTIL_H
#define _UTIL_H

enum Directions{
    UP = 0,
    HORIZONTAL,
    DOWN
};

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
} Point;

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

TournObject ** tourn;

#endif