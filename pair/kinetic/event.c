#include"event.h"
#include"orderedlist.h"
#include"tourn.h"

#include"splay_tree.h"
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
    CandsNode * up, *newCands, *low;
    if(q == ownerS(p->hitsUp[dir], HITS_UP_TREE, dir)){ /* p is in HitsUp(q) */
        t = NULL;
        up = (CandsNode *)predecessorS(q->candsRoot[dir], p, CANDS_TREE, dir, DOWN);
        if(up != NULL)
            t = up->key;
        else
            t = ownerS(q->hitsUp[dir], HITS_UP_TREE, dir);
        
        newCands = extractS(q->candsRoot[dir], NULL, up, CANDS_TREE, dir);
        newCands = joinS(detach(p->candsRoot[dir], CANDS_TREE, dir), newCands, CANDS_TREE, dir);
        attach(p->candsRoot[dir], newCands, CANDS_TREE, dir);
        /* check if some lcand changed */
        /* delete p from HitsUp(q) */
        deleteS(q->hitsUpRoot[dir], p, HITS_UP_TREE, dir);
        /* insert p in HitsUp(t) (if t != NULL)*/
        if(t != NULL)
            insertS(t->hitsUpRoot[dir], p, HITS_UP_TREE, dir);

        w = ownerS(q->hitsLow[dir], HITS_LOW_TREE, dir);
        if(w != NULL)
            deleteS(w->hitsLowRoot[dir], q, HITS_LOW_TREE, dir);
        insertS(p->hitsLowRoot[dir], q, HITS_LOW_TREE, dir);
    }
    else if(p == ownerS(q->hitsLow[dir], HITS_LOW_TREE, dir)){ /* q is in HitsLow(p) */
        /* searching for low(q) in Cands(p) */        
        low = (CandsNode *)predecessorS(p->candsRoot[dir], p, CANDS_TREE, dir, UP);
        if(low != NULL)
            t = low->key;
        else
            t = ownerS(p->hitsLow[dir], HITS_LOW_TREE, dir);

        newCands = extractS(p->candsRoot[dir], low, NULL, CANDS_TREE, dir);
        newCands = joinS(detach(q->candsRoot[dir], CANDS_TREE, dir), newCands, CANDS_TREE, dir);
        attach(q->candsRoot[dir], newCands, CANDS_TREE, dir);
        /* check if some lcand changed */

        deleteS(p->hitsLowRoot[dir], q, HITS_LOW_TREE, dir);
        if(t != NULL)
            insertS(t->hitsLowRoot[dir], q, HITS_LOW_TREE, dir);

        w = ownerS(p->hitsUp[dir], HITS_UP_TREE, dir);

        if(w != NULL)
            deleteS(w->hitsUpRoot[dir], p, HITS_UP_TREE, dir);
        insertS(q->hitsUpRoot[dir], p, HITS_UP_TREE, dir);        
    }

    db(
        printf("Printing point %c\n", p->name);
        printPoint(p, dir);
        printf("Printing point %c\n", q->name);
        printPoint(q, dir);
    );
}

/* +60-order event */
void upEvent(Point * p, Point * q, int dir){    
    HitsNode * auxh, *newHits;
    Point * v, *t;
    if(q == ownerS(p->hitsLow[dir], HITS_LOW_TREE, dir)){ /* p is in HitsLow(q) */
        v = ownerS(q->cands[dir], CANDS_TREE, dir); /* search for q in Cands(v) */
        if(v != NULL)
            /* check if some lcand changed */
            deleteS(v->candsRoot[dir], q, CANDS_TREE, dir);
        
        /* check if some lcand changed */
        insertS(p->candsRoot[dir], q, CANDS_TREE, dir);
        
        auxh = (HitsNode *)successorS(q->hitsUpRoot[dir], p, HITS_UP_TREE, dir, HORIZONTAL);
        
        newHits = extractS(q->hitsUpRoot[dir], NULL, auxh, HITS_UP_TREE, dir);
        newHits = joinS(detach(p->hitsUpRoot[dir], HITS_UP_TREE, dir), newHits, HITS_UP_TREE, dir);
        attach(p->hitsUpRoot[dir], newHits, HITS_UP_TREE, dir);

        if(auxh != NULL)
            t = auxh->key;
        else
            t = ownerS(q->hitsLow[dir], HITS_LOW_TREE, dir);
        
        /* remove p from Hits_low(q) */
        deleteS(q->hitsLowRoot[dir], p, HITS_LOW_TREE, dir);

        if(t != NULL)
            insertS(t->hitsLowRoot[dir], p, HITS_LOW_TREE, dir);

    }
    else if(p == ownerS(q->cands[dir], CANDS_TREE, dir)){ /* q is in Cands(p) */
        t = ownerS(p->hitsLow[dir], HITS_LOW_TREE, dir);

        if(t != NULL)
            deleteS(t->hitsLowRoot[dir], p, HITS_LOW_TREE, dir);
        insertS(q->hitsLowRoot[dir], p, HITS_LOW_TREE, dir);

        auxh = (HitsNode *)predecessorS(p->hitsUpRoot[dir], q, HITS_UP_TREE, dir, DOWN);

        if(auxh != NULL)
            v = auxh->key;
        else
            v = ownerS(p->cands[dir], CANDS_TREE, dir);
        
        newHits = extractS(p->hitsUpRoot[dir], auxh, NULL, HITS_UP_TREE, dir);
        newHits = joinS(newHits, detach(q->hitsUpRoot[dir], HITS_UP_TREE, dir), HITS_UP_TREE, dir);
        attach(q->hitsUpRoot[dir], newHits, HITS_UP_TREE, dir);

        /* check if some lcand changed */
        deleteS(p->candsRoot[dir], q, CANDS_TREE, dir);
        if(v != NULL)
            /* check if some lcand changed */
            insertS(v->candsRoot[dir], q, CANDS_TREE, dir);
    }
}

/* -60-order event */
void downEvent(Point * p, Point * q, int dir){    
    HitsNode * auxh, *newHits;
    Point * v, *t;
    if(q == ownerS(p->hitsUp[dir], HITS_UP_TREE, dir)){ /* p is in HitsUp(q) */
        v = ownerS(q->cands[dir], CANDS_TREE, dir); /* search for q in Cands(v) */
        /* check if some lcand changed */
        if(v != NULL)
            deleteS(v->candsRoot[dir], q, CANDS_TREE, dir);
        /* check if some lcand changed */
        insertS(p->candsRoot[dir], q, CANDS_TREE, dir);
        
        auxh = (HitsNode *)successorS(q->hitsLowRoot[dir], p, HITS_LOW_TREE, dir, HORIZONTAL);
        
        newHits = extractS(q->hitsLowRoot[dir], NULL, auxh, HITS_LOW_TREE, dir);
        newHits = joinS(detach(p->hitsLowRoot[dir], HITS_LOW_TREE, dir), newHits, HITS_LOW_TREE, dir);
        attach(p->hitsLowRoot[dir], newHits, HITS_LOW_TREE, dir);

        if(auxh != NULL)
            t = auxh->key;
        else
            t = ownerS(q->hitsUp[dir], HITS_UP_TREE, dir);
        
        /* remove p from Hits_low(q) */
        deleteS(q->hitsUpRoot[dir], p, HITS_UP_TREE, dir);

        if(t != NULL)
            insertS(t->hitsUpRoot[dir], p, HITS_UP_TREE, dir);

    }
    else if(p == ownerS(q->cands[dir], CANDS_TREE, dir)){ /* q is in Cands(p) */
        t = ownerS(p->hitsUp[dir], HITS_UP_TREE, dir);

        if(t != NULL)
            deleteS(t->hitsUpRoot[dir], p, HITS_UP_TREE, dir);
        insertS(q->hitsUpRoot[dir], p, HITS_UP_TREE, dir);

        auxh = (HitsNode *)predecessorS(p->hitsLowRoot[dir], q, HITS_LOW_TREE, dir, UP);

        if(auxh != NULL)
            v = auxh->key;
        else
            v = ownerS(p->cands[dir], CANDS_TREE, dir);
        
        newHits = extractS(p->hitsLowRoot[dir], auxh, NULL, HITS_LOW_TREE, dir);
        newHits = joinS(newHits, detach(q->hitsLowRoot[dir], HITS_LOW_TREE, dir), HITS_LOW_TREE, dir);
        attach(q->hitsLowRoot[dir], newHits, HITS_LOW_TREE, dir);

        deleteS(p->candsRoot[dir], q, CANDS_TREE, dir);
        if(v != NULL)
            insertS(v->candsRoot[dir], q, CANDS_TREE, dir);
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
            /* tournEvent(); */
        }
        else{
            listEvent();
        }
    }
}