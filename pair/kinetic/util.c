#include "util.h"

int checkLine(Point * a, Point * c, double theta){    
    double x;

    x = (cos(theta))*(getYCoordinate(c) - getYCoordinate(a));
    x -= (sin(theta))*(getXCoordinate(c) - getXCoordinate(a));

    if(x > EPS)
        x = 1;
    else if(x < -EPS)
        x = -1;
    else
        x = 0;

    return (int)x;
}