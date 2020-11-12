#include"event.h"
#include"orderedlist.h"
#include"tourn.h"
#include"hits.h"
#include"cands.h"
#include<stdio.h>

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

    dir = eventType;
    p = aux->p;
    q = p->prev[eventType];

    listSwap(p, q, dir);
        
    p = p->next[dir];
    
    updateListCert(p, dir);
    updateListCert(p->prev[dir], dir);
    updateListCert(p->next[dir], dir);    
}

/* horizontal-order event */
void horizontalEvent(Point * p, Point * q, int dir){
    Point * t, *w;
    CandsNode * aux;
    if(q == queryHitsUp(p, dir)){ /* p is in HitsUp(q) */
        t = NULL;
        aux = querySuccessorCands(q->candsRoot[dir], p, DOWN, dir);
        if(aux != NULL){
            t = aux->key;
        }
        else{
            t = queryHitsUp(q, dir);
            if(t == NULL){
                aux = NULL;
            }
            else{
                aux = t->cands[dir];
            }
        }        
        joinCands(p->candsRoot[dir], extractCands(q->candsRoot[dir], NULL, aux, dir), dir);
        /*TODO: check if some lcand changed */
        /* delete p from HitsUp(q) */
        deleteHits(q->hitsUpRoot[dir], p, dir, 1);
        /* insert p in HitsUp(t) (if t != NULL)*/
        if(t != NULL)
            insertHits(t->hitsUpRoot[dir], p, dir, 1);

        w = queryHitsLow(q, dir);
        if(w != NULL)
            deleteHits(w->hitsLowRoot[dir], q, dir, 0);
        insertHits(p->hitsLowRoot[dir], q, dir, 0);
    }
    else if(p == queryHitsLow(q, dir)){ /* q is in HitsLow(p) */
        t = queryPredecessorCands(p->candsRoot[dir], q, UP, dir)->key;
        if(t == NULL){
            t = queryHitsLow(p, dir);
        }
        joinCands(q->candsRoot[dir], extractCands(p->candsRoot[dir], t->cands[dir], NULL, dir), dir);

        deleteHits(p->hitsLowRoot[dir], q, dir, 0);
        if(t != NULL)
            insertHits(t->hitsLowRoot[dir], q, dir, 0);
        w = queryHitsUp(p, dir);
        if(w != NULL)
            deleteHits(w->hitsUpRoot[dir], p, dir, 1);
        insertHits(q->hitsUpRoot[dir], p, dir, 1);        
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