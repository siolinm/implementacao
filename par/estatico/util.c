#include"util.h"


void init(int m){
    points = NULL;
    points = malloc((m+1)*sizeof(*points));
}

void destroy(){
    int i;
    for(i = 1; i <= n; i++)
        free(points[i]);
    free(points);
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
    double x;
    b.x = cos(theta) + getXCoordinate(a);
    b.y = sin(theta) + getYCoordinate(a);

    x = (b.x - getXCoordinate(a))*(getYCoordinate(c) - getYCoordinate(a));
    x -= (b.y - getYCoordinate(a))*(getXCoordinate(c) - getXCoordinate(a));

    if(x > EPS)
        x = 1;
    else if(x < -EPS)
        x = -1;
    else
        x = 0;

    return (int)x;
}

double distance(Point * a, Point * b){
    return sqrt((a->x - b->x)*(a->x - b->x) + (a->y - b->y)*(a->y - b->y));
}