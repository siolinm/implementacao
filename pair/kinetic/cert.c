#include"cert.h"
#include"tourn.h"
#include"hits.h"
#include"cands.h"
#include<stdio.h>

void initCertTourn(int dir){
    int i;
    TournObject * a;    
    /* initializes tourn certificates */
    for(i = 2*tournElem - 1; i >= n; i--){
        a = tourn[i];
                
        newCertTourn(a);
    }
}

/* 
 * assuming d(a, lcand(a)) <= d(b, lcand(b)) 
 * 
 * goal: t such that d(a, lcand(a)) >= d(b, lcand(b)) in [t, t + eps] eps > 0
 * 
 * (1)  (x(a) - x(lcand(a)))^2 + (y(a) - y(lcand(a)))^2 >= (x(b) - x(lcand(b)))^2 + (y(b) - y(lcand(b)))^2
 * 
 * x(a) = x_0(a) + t*speed(a).x
 * y(a) = y_0(a) + t*speed(a).y
 * 
 * let c_1 = speed(a).x - speed(lcand(a)).x
 * c_2 = x_0(a) - x_0(lcand(a))
 * c_3 = speed(a).y - speed(lcand(a)).y
 * c_4 = y_0(a) - y_0(lcand(a))
 * 
 * c_5, c_6, c_7 and c_8 are similar but to point b
 * 
 * Rewriting (1):
 * 
 * (tc_1 + c_2)^2 + (tc_3 + c_4)^2 >= (tc_5 + c_6)^2 + (tc_7 + c_8)^2
 * ....
 * t^2(c_1^2 + c_3^2 - c_5^2 - c_7^2) + 2t(c_1c_2 + c_3c_4 - c_5c_6 - c_7c_8) + c_2^2 + c_4^2 - c_6^2 - c_8^2 >= 0
 * 
 * m = (c_1^2 + c_3^2 - c_5^2 - c_7^2)
 * n = 2(c_1c_2 + c_3c_4 - c_5c_6 - c_7c_8)
 * o = c_2^2 + c_4^2 - c_6^2 - c_8^2
 * 
 * mt^2 + nt + o >= 0
 * 
 * Cases:
 * if m > 0, then n^2 - 4mo must be > 0
 * return is the bigger root
 * 
 * if m < 0 and n^2 - 4mo <= 0 return INF
 * 
 * if m < 0 and n^2 - 4mo > 0 return smaller root
 * 
 * if m = 0:
 *      nt + o >= 0
 * 
 *      n > 0 return -o/n
 * 
 *      n < 0 return INF
 *      
 *      if n = 0:
 *          o must be <= 0
 *          return INF
 * 
 */
double expireTourn(TournObject * a, TournObject * b){
    if(a->lcandp == NULL || b->lcandp == NULL)
        return INFINITE;
    int i, j;
    TournObject * aux;
    double c[9], m, n, o, delta, t1, t2;
    aux = a;
    for(i = 0; i < 2; i++){
        c[4*i + 1] = getVx(aux->p, aux->direction) - getVx(aux->lcandp, aux->direction);
        c[4*i + 2] = getX0(aux->p, aux->direction) - getX0(aux->lcandp, aux->direction);
        c[4*i + 3] = getVy(aux->p, aux->direction) - getVy(aux->lcandp, aux->direction);
        c[4*i + 4] = getY0(aux->p, aux->direction) - getY0(aux->lcandp, aux->direction);
        aux = b;
    }

    m = c[1]*c[1] + c[3]*c[3] - c[5]*c[5] - c[7]*c[7];
    n = 2*(c[1]*c[2] + c[3]*c[4] - c[5]*c[6] - c[7]*c[8]);
    o = c[2]*c[2] + c[4]*c[4] - c[6]*c[6] - c[8]*c[8];
    delta = n*n - 4*m*o;

    if(m > 0){
        if(delta <= 0){
            printf("Something gone wrong! Delta isn't positive\n");
        }
        else{
            t1 = -n + sqrt(delta);
            t1 = t1/2*m;
            t2 = -n - sqrt(delta);
            t2 = t2/2*m;

            if(t1 < t2)
                t1 = t2;
        }
    }
    else if (m < 0){
        if(delta <= 0)
            return INFINITE;
        
        t1 = -n + sqrt(delta);
        t1 = t1/2*m;
        t2 = -n - sqrt(delta);
        t2 = t2/2*m;

        if(t1 > t2)
            t1 = t2;
    }
    else{
        if(n > 0){
            t1 = -o/n;
        }
        else if(n < 0){
            t1 = INFINITE;
        }
        else{
            if(o > 0){
                printf("Something gone wrong! o > 0\n");
            }
            else{
                t1 = INFINITE;
            }
        }
    }
}

double expireList(Point *a, Point * b, int dir){
    if(b == NULL)
        return INFINITE;

    double aspeed, bspeed;
    aspeed = getVx(a, dir); 
    bspeed = getVx(b, dir);

    if(aspeed - bspeed >= 0)
        return INFINITE;

    return (getX0(a, dir) - getX0(b, dir))/(bspeed - aspeed);
}

void newCertTourn(TournObject * obj){
    int i, dir;
    Cert * newCert = malloc(sizeof(*newCert));
    PQObject * pq = malloc(sizeof(*pq));

    dir = obj->direction;
    obj->p->cert[TOURN_CERT + dir] = newCert;
    i = obj->p->lastMatch[dir];

    if(i == 1){
        newCert->value = INFINITE;
    }
    else{
        newCert->value = expireTourn(tourn[i/2], tourn[i]);
    }

    pq->certType = TOURN_CERT + dir;
    pq->p = obj->p;

    insertPQ(pq);
}

void newCertList(Point *p, int dir){
    if(p == NULL)
        return;
    Cert * cert = malloc(sizeof(*cert));
    PQObject * pq = malloc(sizeof(*pq));

    p->cert[dir] = cert;
    p->cert[dir]->value = expireList(p, p->prev[dir], dir);

    if(dir == HORIZONTAL)
        pq->certType = HORIZONTAL_CERT;
    else if(dir == UP)
        pq->certType = UP_CERT;
    else if(dir == DOWN)
        pq->certType = DOWN_CERT;
    
    pq->p = p;    

    insertPQ(pq);
}

void updateTournCert(TournObject * a){
    int i, dir;
    Cert * cert = a->p->cert[TOURN_CERT + dir];

    dir = a->direction;
    i = a->p->lastMatch[dir];

    if(i == 1){
        cert->value = INFINITE;
        updatePQ(Q[cert->pqpos], cert->value);
        return;
    }

    cert->value = expireTourn(tourn[i/2], tourn[i]);

    updatePQ(Q[cert->pqpos], cert->value);
}

void updateListCert(Point * p, int dir){
    if(p == NULL)
        return;
    
    int certType;

    if(dir == HORIZONTAL)
        certType = HORIZONTAL_CERT;
    else if(dir == UP)
        certType = UP_CERT;
    else if(dir == DOWN)
        certType = DOWN_CERT;

    Cert * cert = p->cert[certType];
    
    updatePQ(Q[cert->pqpos], expireList(p, p->prev[dir], dir));
}

void tournEvent(){
    PQObject * aux = minPQ();
    int dir, j, k;
    dir = aux->certType - TOURN_CERT;

    j = aux->p->lastMatch[dir];
    k = 2*(j/2) + !(j % 2);
    
    while(j > 1 && compareTourn(j, k)){
        tourn[j/2] = tourn[j];
        k = 2*(j/2) + !(j % 2);
        tourn[k]->p->lastMatch[dir] = k;
        updateTournCert(tourn[k]);
        
        j = j/2;
        k = 2*(j/2) + !(j % 2);
    }
    
    tourn[j]->p->lastMatch[dir] = j;
    updateTournCert(tourn[j]);

}

void listEvent(){
    PQObject * aux = minPQ();
    Point * p, * q;
    int dir, eventType;
    p = aux->p;

    if(aux->certType == HORIZONTAL_CERT){
        eventType = HORIZONTAL;
    }
    else if(aux->certType == UP_CERT){
        eventType = UP;
    }
    else{
        eventType = DOWN;
    }

    q = p->prev[eventType];
    if(eventType == HORIZONTAL){
        /* q must be above p */
        if(getY(p, HORIZONTAL) > getY(q, HORIZONTAL)){
            p = q;
            q = aux->p;
        }

        horizontalEvent(p, q, HORIZONTAL);
    }
    else if(eventType == UP){
        /* p must be to the left of q */
        if(getX(p, HORIZONTAL) > getX(q, HORIZONTAL)){
            p = q;
            q = aux->p;
        }

        upEvent(p, q, HORIZONTAL);
    }
    else if(eventType == DOWN){
        if(getX(p, HORIZONTAL) > getX(q, HORIZONTAL)){
            p = q;
            q = aux->p;
        }

        downEvent(p, q, HORIZONTAL);
    }

    AVLNode * aux;
    Point * auxp;
    dir = eventType;
    p = aux->p;
    q = p->prev[eventType];
    
    /* swap list nodes */
    aux = p->listPosition[dir];
    p->listPosition[dir] = q->listPosition[dir];
    q->listPosition[dir] = aux;

    /* swap linked list positions */
    p->prev[dir] = q->prev[dir];
    if(p->prev[dir])
        p->prev[dir]->next[dir] = p;

    q->next[dir] = p->next[dir];
    if(q->next[dir])
        q->next[dir]->prev[dir] = q;

    p->next[dir] = q;
    q->prev[dir] = p;

    p = p->next[dir];
    
    updateListCert(p, dir);
    updateListCert(p->prev[dir], dir);
    updateListCert(p->next[dir], dir);    
}

/* horizontal-order event */
void horizontalEvent(Point * p, Point * q, int dir){
    Point * t, *w;    
    if(q == queryHitsUp(p, dir)){ /* p is in HitsUp(q) */
        t = querySuccessorCands(q->candsRoot[dir], p, DOWN, dir);
        joinCands(p->candsRoot[dir], extractCands(q->candsRoot[dir], NULL, t, dir), dir);
        /*TODO: check if some lcand changed */
        if(t == NULL){
            t = queryHitsUp(q, dir);
        }
        /* delete p from HitsUp(q) */
        deleteHits(q->hitsUpRoot[dir], p, dir);
        /* insert p in HitsUp(t) (if t != NULL)*/
        if(t != NULL)
            insertHits(t->hitsUpRoot[dir], p, dir);

        w = queryHitsLow(q, dir);
        if(w != NULL)
            deleteHits(w->hitsLowRoot[dir], q, dir);
        insertHits(p->hitsLowRoot[dir], q, dir);
    }
    else if(p == queryHitsLow(q, dir)){ /* q is in HitsLow(p) */
        t = queryPredecessorCands(p->candsRoot[dir], q, UP, dir);
        joinCands(q->candsRoot[dir], extractCands(p->candsRoot[dir], t, NULL, dir), dir);
        if(t == NULL){
            t = queryHitsLow(p, dir);
        }

        deleteHits(p->hitsLowRoot[dir], q, dir);
        if(t != NULL)
            insertHits(t->hitsLowRoot[dir], q, dir);
        w = queryHitsUp(p, dir);
        if(w != NULL)
            deleteHits(w->hitsUpRoot[dir], p, dir);
        insertHits(q->hitsUpRoot[dir], p, dir);        
    }
}

/* +60-order event */
void upEvent(Point * p, Point * q, int dir){
    Point * v;
    if(q == queryHitsLow(p, dir)){ /* p is in HitsLow(q) */
        v = queryCands(q, dir);
        if(v != NULL)
            deleteCands(v->candsRoot[dir], q, dir);
        insertCands(p->candsRoot[dir], q, dir);
        /* query for successor in horizontal order */


    }
    else if(p == queryCands(q, dir)){

    }
}

/* -60-order event */
void downEvent(Point * p, Point * q, int dir){
    if(dir == HORIZONTAL){
        
    }
}

/* 
    The first certificate in the PQ has expired
*/
void event(){
    PQObject *aux;
    while(valuePQ(1) == now){
        aux = minPQ();
        if(aux->certType >= TOURN_CERT){
            tournEvent();
        }
        else{
            listEvent();
        }
    }
}