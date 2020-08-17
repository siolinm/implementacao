#include<stdlib.h>
#ifndef _UTIL_H
#define _UTIL_H

typedef struct Point
{
    double x;
    double y;
} Point;

/*
    Coordinate system rotation
*/
double angle;

/*
    Vector of points
*/
Point ** points;

/*
    Number of points
*/
int n;

/*
    Allocates memory for m points
*/
void init(int m);

/*
    Get x coordinate from points[i] in the coordinate system rotated by angle
*/
double getXCoordinate(Item * a);

/*
    Get y coordinate from points[i] in the coordinate system rotated by angle
*/
double getYCoordinate(Item * a);

/*
    Swaps values in index i and j from points
*/
void swapPoints(int i, int j);

#endif