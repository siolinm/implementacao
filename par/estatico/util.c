#include"util.h"
#include"math.h"

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