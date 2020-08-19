#include"util.h"

void init(int m){
    points = malloc((m+1)*sizeof(*points));
}

double getXCoordinate(Point * a){
    return (a->x)*cos(angle) + (a->y)*sin(angle);
}

double getYCoordinate(Point * a){
    return -(a->x)*sin(angle) + (a->y)*cos(angle);
}

void swapPoints(int i, int j){
    Point * aux;
    aux = points[i];
    points[i] = points[j];
    points[j] = aux;    
}

int checkLine(Point * a, Point * c, double theta){
    Point b;
    /*
        b.x = cos(theta)*(getXCoordinate(a) + 1) - sin(theta)*(getYCoordinate(a));
        b.y = sin(theta)*(getXCoordinate(a) + 1) + cos(theta)*(getYCoordinate(a));
    */
    b.x = cos(theta) + getXCoordinate(a);
    b.y = sin(theta) + getYCoordinate(a);

    double x = (b.x - getXCoordinate(a))*(getYCoordinate(c) - getYCoordinate(a));
    x -= (b.y - getYCoordinate(a))*(getXCoordinate(c) - getXCoordinate(a));

    if(x > 0)
        x = 1;
    else if(x < 0)
        x = -1;

    return (int)x;
}