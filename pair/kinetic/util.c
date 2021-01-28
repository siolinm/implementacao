#include "util.h"
#include"splay_tree.h"

double getX(Point * p, int direction){
    double ret = 1;
    
    if(direction < 0){
        direction = -direction;
        ret = -ret;
    }

    return ret*(getX0(p, direction) + now*getVx(p, direction));
}

double getY(Point * p, int direction){
    double ret = 1;
    
    if(direction < 0){
        direction = -direction;
        ret = -ret;
    }

    return ret*(getY0(p, direction) + now*getVy(p, direction));
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

void printPoint(Point * p, int dir){
    Point * hlow, *hup, *cand;
    printf("Direction: ");
    if(dir == HORIZONTAL)
        printf("HORIZONTAL");
    else if(dir == UP)
        printf("UP");
    else
        printf("DOWN");
    
    printf("\n");
    printf("Point: %c\n", p->name);
    printf("x0: (%g, %g), speed: (%g, %g)\n", p->x0.x, p->x0.y, p->speed.x, p->speed.y);
    printf("Current position: (%g, %g)\n", getX(p, dir), getY(p, dir));
    
    cand = ownerS(p->cands[dir], CANDS_TREE, dir);
    if(cand)
        printf("%c is in Cands(%c)\n", p->name, cand->name);
    hup = ownerS(p->hitsUp[dir], HITS_UP_TREE, dir);
    if(hup)
        printf("%c is in Hits_up(%c)\n", p->name, hup->name);
    hlow = ownerS(p->hitsLow[dir], HITS_LOW_TREE, dir);
    if(hlow)
        printf("%c is in Hits_low(%c)\n", p->name, hlow->name);
        
    printf("Cands(%c) = \n", p->name);
    printS(p->candsRoot[dir], CANDS_TREE);
    printf("Hits_up(%c) = \n", p->name);
    printS(p->hitsUpRoot[dir], HITS_UP_TREE);
    printf("Hits_low(%c) = \n", p->name);
    printS(p->hitsLowRoot[dir], HITS_LOW_TREE);
    if(p->next[dir])
        printf("Next: %c\n", p->next[dir]->name);
    if(p->prev[dir])
        printf("Prev: %c\n", p->prev[dir]->name);
}

int updateLcand(Point * p, int dir){
    Point * lcand = NULL;
    int retval = 0;
    
    if(p->candsRoot[dir]->parent)
        /* leftmost can't be NULL */
        lcand = getKeyS(p->candsRoot[dir]->parent->leftmost, CANDS_TREE);
    
    if(p->lcand[dir] != lcand)
        retval = 1;

    p->lcand[dir] = lcand;

    return retval;
}

int getDirection(int certType){
    int retval;
    if(certType == HORIZONTAL_CERT)
        retval = HORIZONTAL;
    else if(certType == UP_CERT)
        retval = UP;
    else if(certType == DOWN_CERT)
        retval = DOWN;
    else
        retval = certType - TOURN_CERT;
    
    return retval;
}

void destroy(){

}