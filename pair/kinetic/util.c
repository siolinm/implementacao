#include "util.h"

double getX(Point * p, int direction){
    return getX0(p, direction) + now*getVx(p, direction);
}

double getY(Point * p, int direction){
    return getY0(p, direction) + now*getVy(p, direction);
}

double getX0(Point * p, int direction){
    double angle = 0;

    if(direction == UP){
        angle = PI_3;
    }
    else if(direction == DOWN){
        angle = -PI_3;
    }

    return (p->x0.x)*cos(angle) + (p->x0.y)*sin(angle);    
}

double getY0(Point * p, int direction){
    double angle = 0;

    if(direction == UP){
        angle = PI_3;
    }
    else if(direction == DOWN){
        angle = -PI_3;
    }

    return -(p->x0.x)*sin(angle) + (p->x0.y)*cos(angle);
}

double getVx(Point * p, int direction){
    double angle = 0;

    if(direction == UP){
        angle = PI_3;
    }
    else if(direction == DOWN){
        angle = -PI_3;
    }

    return (p->speed.x)*cos(angle) + (p->speed.y)*sin(angle);
}

double getVy(Point * p, int direction){
    double angle = 0;

    if(direction == UP){
        angle = PI_3;
    }
    else if(direction == DOWN){
        angle = -PI_3;
    }

    return -(p->speed.x)*sin(angle) + (p->speed.y)*cos(angle);
}

double distance(Point * a, Point * b, int direction){
    double dx, dy;
    if(a == NULL || b == NULL)
        return INFINITE;
    dx = (getX(a, direction) - getX(b, direction));
    dy = (getY(a, direction) - getY(b, direction));    
    return sqrt(dx*dx + dy*dy);
}

int certType(int direction){
    if(direction == UP)
        return UP_CERT;
    if(direction == DOWN)
        return DOWN_CERT;

    return HORIZONTAL_CERT;
}

int checkLine(Point * a, Point * c, double theta, int dir){    
    double x;

    x = (cos(theta))*(getY(c, dir) - getY(a, dir));
    x -= (sin(theta))*(getX(c, dir) - getX(a, dir));

    if(x > EPS)
        x = 1;
    else if(x < -EPS)
        x = -1;
    else
        x = 0;

    return (int)x;
}

void destroy(){

}