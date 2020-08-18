#include"math.h"
#include<stdlib.h>
#ifndef _UTIL_H
#define _UTIL_H

#define PI_3 acos(0.5)

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
double getXCoordinate(Point * a);

/*
    Get y coordinate from points[i] in the coordinate system rotated by angle
*/
double getYCoordinate(Point * a);

/*
    Swaps values in index i and j from points
*/
void swapPoints(int i, int j);

/*

*/
int checkLine(Point * a, Point * c, double theta);


#endif