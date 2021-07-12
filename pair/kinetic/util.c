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
    double angle = PI_3;

    if(direction == HORIZONTAL){
        angle = 0;
    }
    else if(direction == DOWN){
        angle = -PI_3;
    }

    return (p->x0.x)*cos(angle) + (p->x0.y)*sin(angle);
}

double getY0(Point * p, int direction){
    double angle = PI_3;

    if(direction == HORIZONTAL){
        angle = 0;
    }
    else if(direction == DOWN){
        angle = -PI_3;
    }

    return -(p->x0.x)*sin(angle) + (p->x0.y)*cos(angle);
}

double getVx(Point * p, int direction){
    double angle = PI_3;

    if(direction == HORIZONTAL){
        angle = 0;
    }
    else if(direction == DOWN){
        angle = -PI_3;
    }

    return (p->speed.x)*cos(angle) + (p->speed.y)*sin(angle);
}

double getVy(Point * p, int direction){
    double angle = PI_3;

    if(direction == HORIZONTAL){
        angle = 0;
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
    else if(certType == ALL_CERT)
        retval = 3;
    else
        retval = certType - TOURN_CERT;

    return retval;
}

int left(Point *p, Point *q, int dir){
    double vxp, vxq, vyp, vyq, aux;
    if(getX(p, dir) < getX(q, dir) - EPS){
        return 1;
    }
    else if(getX(q, dir) < getX(p, dir) - EPS){
        return 0;
    }
    else{
        if(getY(p, dir) > getY(q, dir) + EPS)
            return 1;
        else if(getY(p, dir) < getY(q, dir) - EPS)
            return 0;
        else{
            vxp = getVx(p, dir);
            vxq = getVx(q, dir);

            aux = max(mod(vxp), mod(vxq));

            vxp -= aux;
            vxq -= aux;

            if(vxp < vxq - EPS) /* p is to the left after t+epsilon (was to the right) */
                return 1;
            else if(vxq < vxp - EPS)/* q is to the left after t+epsilon (was to the right) */
                return 0;
            else{
                vyp = getVy(p, dir);
                vyq = getVy(q, dir);

                aux = max(mod(vyp), mod(vyq));

                vyp -= aux;
                vyq -= aux;
                if(vyp < vyq - EPS) /* p is below q after t+epsilon (was above, therefore to the left) */
                    return 0;
                else
                    return 1;
            }
        }
    }
}

int wasLeft(Point *p, Point *q, int dir){
    double vxp, vxq, vyp, vyq, aux;
    if(getX(p, dir) < getX(q, dir) - EPS){
        return 1;
    }
    else if(getX(q, dir) < getX(p, dir) - EPS){
        return 0;
    }
    else{
        if(getY(p, dir) > getY(q, dir) + EPS)
            return 1;
        else if(getY(p, dir) < getY(q, dir) - EPS)
            return 0;
        else{
            vxp = getVx(p, dir);
            vxq = getVx(q, dir);

            aux = max(mod(vxp), mod(vxq));

            vxp -= aux;
            vxq -= aux;

            if(vxp < vxq - EPS) /* p is to the left after t+epsilon (was to the right) */
                return 0;
            else if(vxq < vxp - EPS)/* q is to the left after t+epsilon (was to the right) */
                return 1;
            else{
                vyp = getVy(p, dir);
                vyq = getVy(q, dir);

                aux = max(mod(vyp), mod(vyq));

                vyp -= aux;
                vyq -= aux;
                if(vyp < vyq - EPS) /* p is below q after t+epsilon (was above, therefore to the left) */
                    return 1;
                else
                    return 0;
            }
        }
    }
}

int getCertPriority(Point * p, Point * q, int dir){
    if(wasLeft(q, p, UP)){ /* Case 1 */
        if(dir == UP)
            return HIGH_PRIORITY;
        else if(dir == DOWN)
            return MEDIUM_PRIORITY;
        else
            return LOW_PRIORITY;
    }
    else if(wasLeft(q, p, DOWN)){ /* Case 3 */
        if(dir == UP)
            return MEDIUM_PRIORITY;
        else if(dir == DOWN)
            return LOW_PRIORITY;
        else
            return HIGH_PRIORITY;
    }
    else{ /* Case 2 */
        if(dir == UP)
            return LOW_PRIORITY;
        else if(dir == DOWN)
            return HIGH_PRIORITY;
        else
            return MEDIUM_PRIORITY;
    }
}

int auxDir(int dir){
    if(dir < 0){
        if(dir == -7)
            return UP;
        else
            return -dir;
    }
    return dir;
}

int leftTest(Point * p, Point * q, int dir){
    int auxdir, prio;
    Point * cert_point;
    Point * left_point, * right_point;
    PQObject * pq;
    Cert * c;
    if(getX(p, dir) < getX(q, dir) - EPS){
        return 1;
    }
    else if(getX(q, dir) < getX(p, dir) - EPS){
        return 0;
    }
    else{
        if(getY(p, dir) > getY(q, dir) + EPS)
            return 1;
        else if(getY(p, dir) < getY(q, dir) - EPS)
            return 0;
        else{
            auxdir = auxDir(dir);
            left_point = p;
            right_point = q;
            if(wasLeft(q, p, HORIZONTAL)){
                left_point = q;
                right_point = p;
            }
            prio = getCertPriority(left_point, right_point, auxdir);
            pq = Q[1];
            if(pq == NULL)
                return left(p, q, dir);
            cert_point = pq->p;
            c = cert_point->cert[pq->certType];
            /* pego o evento no topo da fila atualmente */
            /* checo se a troca entre p e q deveria ser processada
            antes ou depois desse evento */
            if(prio > c->priority){
                return left(p, q, dir);
            }
            else if(prio < c->priority){
                return wasLeft(p, q, dir);
            }
            else{
                right_point = q;
                if(wasLeft(q, p, dir))
                    right_point = p;
                if(prio == 1)
                    prio = 2;
                if(((-certType(dir) + (3 - prio)) % 3) < ((-pq->certType + (3 - prio)) % 3)){
                    return left(p, q, dir);
                }
                else if(((-certType(dir) + (3 - prio)) % 3) > ((-pq->certType + (3 - prio)) % 3)){
                    return wasLeft(p, q, dir);
                }
                else{
                    if(right_point->id < cert_point->id)
                        return left(p, q, dir);
                    else if(right_point->id > cert_point->id)
                        return wasLeft(p, q, dir);
                    else{
                        return left(p, q, dir);
                    }
                }
                // if(right_point->id < cert_point->id)
                //     return left(p, q, dir);
                // else if(right_point->id > cert_point->id)
                //     return wasLeft(p, q, dir);
                // else{
                //     if(certType(dir) < pq->certType){
                //         return left(p, q, dir);
                //     }
                //     else if(certType(dir) > pq->certType){
                //         return wasLeft(p, q, dir);
                //     }
                //     else
                //         return left(p, q, dir);
                // }
            }
        }
    }
}

void destroy(){

}