#include"event.h"
#include"orderedlist.h"
#include"tourn.h"

#include"splay_tree.h"
#include"draw.h"
#include<stdio.h>

#define module(x) (x > 0 ? x : -x)
#define max(a, b) (a > b ? a : b)

void tournEvent(){
    PQObject * aux = minPQ();
    int dir, j, k;
    dir = aux->certType - TOURN_CERT;

    j = aux->p->lastMatch[dir];
    k = 2*(j/2) + !(j % 2);
    // db(printf("Tourn event between %d and %d\n", j, k););

    tourn[j/2] = tourn[j];
    dir = tourn[k]->direction;
    tourn[k]->p->lastMatch[dir] = k;
    updateTournCert(tourn[k]);

    j = j/2;
    k = 2*(j/2) + !(j % 2);

    while(j > 1 && compareTourn(j, k)){
        tourn[j/2] = tourn[j];
        dir = tourn[k]->direction;
        tourn[k]->p->lastMatch[dir] = k;
        updateTournCert(tourn[k]);

        j = j/2;
        k = 2*(j/2) + !(j % 2);
    }

    dir = tourn[j]->direction;
    tourn[j]->p->lastMatch[dir] = j;
    updateTournCert(tourn[j]);
    // db(
    //     printTourn();
    // );
}

void listEvent(Point * p, int eventType){
    int dir, skip = 1, prio;
    Point * auxp, *q;
    char text[100];

    q = p->prev[getDirection(eventType)];
    auxp = p;
    prio = p->cert[eventType]->priority;

    // printf("Event between %c and %c -- ", p->name, q->name);
    dir = HORIZONTAL;
    sprintf(text, "Event between %c and %c", p->name, q->name);
    drawEvent(p, q, NULL, NULL, 0, dir, text, -1, &skip);

    if(eventType == HORIZONTAL_CERT){
        /* q must be above p */
        if(getY(p, HORIZONTAL) > EPS + getY(q, HORIZONTAL)){ /* Y(p) > Y(q) */
            p = q;
            q = auxp;
        }
        else if(mod(getY(p, HORIZONTAL) - getY(q, HORIZONTAL)) < EPS){
            p = q;
            q = auxp;
        }
        printf("Event between %c and %c -- ", p->name, q->name);
        printf("HORIZONTAL, prio: %d\n", prio);

        horizontalEvent(p, q, HORIZONTAL);
        downEvent(p, q, UP);
        upEvent(q, p, DOWN);
    }
    else if(eventType == UP_CERT){
        /* p must be to the left of q */
        // if(getX(p, HORIZONTAL) - getX(q, HORIZONTAL) > EPS){ /* X(p) > X(q) */
        //     p = q;
        //     q = auxp;
        // }
        /* else if(mod(getX(p, HORIZONTAL) - getX(q, HORIZONTAL)) < EPS){
        } */
        /* */
        /* U (q, p) -- LOW ou MEDIUM */
        if(prio == LOW_PRIORITY || prio == MEDIUM_PRIORITY){
            if(left(q, p, HORIZONTAL)){
                p = q;
                q = auxp;
            }
        }
        else{
            if(wasLeft(q, p, HORIZONTAL)){
                p = q;
                q = auxp;
            }
        }

        printf("Event between %c and %c -- ", p->name, q->name);
        printf("UP, prio: %d\n", prio);
        upEvent(p, q, HORIZONTAL);
        horizontalEvent(q, p, UP);
        downEvent(p, q, DOWN);
    }
    else if(eventType == DOWN_CERT){
        /* p must be to the left of q */
        // if(getX(p, HORIZONTAL) - getX(q, HORIZONTAL) > EPS){ /* X(p) > X(q) */
        //     p = q;
        //     q = auxp;
        // }
        // else if(mod(getX(p, HORIZONTAL) - getX(q, HORIZONTAL)) < EPS){
        //     if(p->prev[HORIZONTAL] == p->prev[DOWN]){
        //         p = q;
        //         q = auxp;
        //     }
        // }
        if(prio == LOW_PRIORITY){
            if(left(q, p, HORIZONTAL)){
                p = q;
                q = auxp;
            }
        }
        else{
            if(wasLeft(q, p, HORIZONTAL)){
                p = q;
                q = auxp;
            }
        }

        printf("Event between %c and %c -- ", p->name, q->name);
        printf("DOWN, prio: %d\n", prio);
        // if(p->name == 'h' && q->name == 'q')
        //     printf("Hello\n");

        downEvent(p, q, HORIZONTAL);
        upEvent(p, q, UP);
        horizontalEvent(p, q, DOWN);
    }

    dir = getDirection(eventType);
    p = auxp;
    q = p->prev[dir];
    listSwap(p, q, dir);

    p = p->next[dir];
    updateListCert(p, dir);
    updateListCert(p->prev[dir], dir);
    updateListCert(p->next[dir], dir);
    for (int i = 1; 2*i < pqSize; i++){
        if(comparePQ(Q[2*i], Q[i])){
            printPQ();
            printf("Incorrect PQ %d and %d, %d\n", 2*i, i, comparePQ(Q[i], Q[2*i]));
            exit(42);
        }
        if(2*i + 1 < pqSize){
            if(comparePQ(Q[2*i + 1], Q[i])){
                printPQ();
                printf("Incorrect PQ %d and %d, %d\n", 2*i + 1, i, comparePQ(Q[i], Q[2*i+1]));
                exit(42);
            }
        }
    }
}

/* horizontal-order event */
void horizontalEvent(Point * p, Point * q, int dir){
    Point * t, *w, *v;
    CandsNode * up, *newCands, *low;
    double vxp, vxq, aux;
    int change, skip = 1;
    char text[200];
    db(
        if(dir == HORIZONTAL){
            printf("Entered HORIZONTAL EVENT: (%c, %c)\n", p->name, q->name);
            // printf("CASE A: %c\n", ownerS(p->hitsUp[dir], HITS_UP_TREE, dir)->name);
        }
    );
    if(q == ownerS(p->hitsUp[dir], HITS_UP_TREE, dir)){ /* p is in HitsUp(q) */
        db(
            if(dir == HORIZONTAL)
                printf("HORIZONTAL EVENT: case A, (%c, %c)\n", p->name, q->name);
        );
        t = NULL;
        up = (CandsNode *)predecessorS(q->candsRoot[dir], p, CANDS_TREE, dir, UP);
        if(up != NULL)
            t = up->key;
        else
            t = ownerS(q->hitsUp[dir], HITS_UP_TREE, dir);

        sprintf(text, "New up(%c) found", p->name);
        drawEvent(p, q, t, NULL, 0, dir, text, HORIZONTAL, &skip);

        newCands = extractS(q->candsRoot[dir], NULL, up, CANDS_TREE, dir);

        sprintf(text, "Extracted these points from Cands(%c) to Cands(%c)", q->name, p->name);
        drawEvent(p, q, t, newCands,
        CANDS_TREE, dir, text, HORIZONTAL, &skip);

        sprintf(text, "Updating lcand(%c)", q->name);
        drawEvent(p, q, t, newCands,
        CANDS_TREE, dir, text, HORIZONTAL, &skip);

        change = updateLcand(q, dir);
        if(change) updateTourn(q, dir);

        newCands = joinS(detach(p->candsRoot[dir], CANDS_TREE, dir), newCands, CANDS_TREE, dir);

        sprintf(text, "Points inserted in Cands(%c)", p->name);
        drawEvent(p, q, t, newCands,
        CANDS_TREE, dir, text, HORIZONTAL, &skip);

        attach(p->candsRoot[dir], newCands, CANDS_TREE, dir);
        /* check if some lcand changed */

        sprintf(text, "Updating lcand(%c)", p->name);
        drawEvent(p, q, t, q->hitsUpRoot[dir]->parent,
        HITS_UP_TREE, dir, text, HORIZONTAL, &skip);

        change = updateLcand(p, dir);
        if(change) updateTourn(p, dir);

        sprintf(text, "Hits_up(%c) before deleting %c", q->name, p->name);
        drawEvent(p, q, t, q->hitsUpRoot[dir]->parent,
        HITS_UP_TREE, dir, text, HORIZONTAL, &skip);

        /* delete p from HitsUp(q) */
        deleteS(q->hitsUpRoot[dir], p, HITS_UP_TREE, dir);

        sprintf(text, "Hits_up(%c) after deleting %c", q->name, p->name);
        drawEvent(p, q, t, q->hitsUpRoot[dir]->parent,
        HITS_UP_TREE, dir, text, HORIZONTAL, &skip);

        /* insert p in HitsUp(t) (if t != NULL)*/
        if(t != NULL){
            sprintf(text, "Hits_up(%c) before inserting %c", t->name, p->name);
            drawEvent(p, q, t, t->hitsUpRoot[dir]->parent,
            HITS_UP_TREE, dir, text, HORIZONTAL, &skip);

            insertS(t->hitsUpRoot[dir], p, HITS_UP_TREE, dir);

            sprintf(text, "Hits_up(%c) after inserting %c", t->name, p->name);
            drawEvent(p, q, t, t->hitsUpRoot[dir]->parent,
            HITS_UP_TREE, dir, text, HORIZONTAL, &skip);
        }

        w = ownerS(q->hitsLow[dir], HITS_LOW_TREE, dir);

        if(w != NULL){
            sprintf(text, "Hits_low(%c) before deleting %c", w->name, q->name);
            drawEvent(p, q, NULL, w->hitsLowRoot[dir]->parent,
            HITS_LOW_TREE, dir, text, HORIZONTAL, &skip);

            deleteS(w->hitsLowRoot[dir], q, HITS_LOW_TREE, dir);

            sprintf(text, "Hits_low(%c) after deleting %c", w->name, q->name);
            drawEvent(p, q, NULL, w->hitsLowRoot[dir]->parent,
            HITS_LOW_TREE, dir, text, HORIZONTAL, &skip);
        }

        sprintf(text, "Hits_low(%c) before inserting %c", p->name, q->name);
        drawEvent(p, q, t, p->hitsLowRoot[dir]->parent,
        HITS_LOW_TREE, dir, text, HORIZONTAL, &skip);

        insertS(p->hitsLowRoot[dir], q, HITS_LOW_TREE, dir);

        sprintf(text, "Hits_low(%c) after inserting %c", p->name, q->name);
        drawEvent(p, q, t, p->hitsLowRoot[dir]->parent,
        HITS_LOW_TREE, dir, text, HORIZONTAL, &skip);
    }
    else if(p == ownerS(q->hitsLow[dir], HITS_LOW_TREE, dir)){ /* q is in HitsLow(p) */
        /* searching for low(q) in Cands(p) */
        db(
            if(dir == HORIZONTAL)
                printf("HORIZONTAL EVENT: case B, (%c, %c)\n", p->name, q->name);
        );
        low = (CandsNode *)predecessorS(p->candsRoot[dir], q, CANDS_TREE, dir, DOWN);
        if(low != NULL)
            t = low->key;
        else
            t = ownerS(p->hitsLow[dir], HITS_LOW_TREE, dir);

        sprintf(text, "New low(%c) found", q->name);
        drawEvent(p, q, t, NULL,
        0, dir, text, HORIZONTAL, &skip);

        newCands = extractS(p->candsRoot[dir], low, NULL, CANDS_TREE, dir);

        sprintf(text, "Extracted these points from Cands(%c) to Cands(%c)", p->name, q->name);
        drawEvent(p, q, t, newCands,
        CANDS_TREE, dir, text, HORIZONTAL, &skip);

        sprintf(text, "Updating lcand(%c)", p->name);
        drawEvent(p, q, t, newCands,
        CANDS_TREE, dir, text, HORIZONTAL, &skip);

        change = updateLcand(p, dir);
        if(change) updateTourn(p, dir);

        newCands = joinS(detach(q->candsRoot[dir], CANDS_TREE, dir), newCands, CANDS_TREE, dir);

        sprintf(text, "Points inserted in Cands(%c)", q->name);
        drawEvent(p, q, t, newCands,
        CANDS_TREE, dir, text, HORIZONTAL, &skip);

        attach(q->candsRoot[dir], newCands, CANDS_TREE, dir);

        sprintf(text, "Updating lcand(%c)", q->name);
        drawEvent(p, q, t, p->hitsLowRoot[dir]->parent,
        HITS_LOW_TREE, dir, text, HORIZONTAL, &skip);

        /* check if some lcand changed */
        change = updateLcand(q, dir);
        if(change) updateTourn(q, dir);

        sprintf(text, "Hits_low(%c) before deleting %c", p->name, q->name);
        drawEvent(p, q, t, p->hitsLowRoot[dir]->parent,
        HITS_LOW_TREE, dir, text, HORIZONTAL, &skip);

        deleteS(p->hitsLowRoot[dir], q, HITS_LOW_TREE, dir);

        sprintf(text, "Hits_low(%c) after deleting %c", p->name, q->name);
        drawEvent(p, q, t, p->hitsLowRoot[dir]->parent,
        HITS_LOW_TREE, dir, text, HORIZONTAL, &skip);

        if(t != NULL){
            sprintf(text, "Hits_low(%c) before inserting %c", t->name, q->name);
            drawEvent(p, q, t, t->hitsLowRoot[dir]->parent,
            HITS_LOW_TREE, dir, text, HORIZONTAL, &skip);

            insertS(t->hitsLowRoot[dir], q, HITS_LOW_TREE, dir);

            sprintf(text, "Hits_low(%c) after inserting %c", t->name, q->name);
            drawEvent(p, q, t, t->hitsLowRoot[dir]->parent,
            HITS_LOW_TREE, dir, text, HORIZONTAL, &skip);
        }

        w = ownerS(p->hitsUp[dir], HITS_UP_TREE, dir);

        if(w != NULL){
            sprintf(text, "Hits_up(%c) before deleting %c", w->name, p->name);
            drawEvent(p, q, t, w->hitsUpRoot[dir]->parent,
            HITS_UP_TREE, dir, text, HORIZONTAL, &skip);

            deleteS(w->hitsUpRoot[dir], p, HITS_UP_TREE, dir);

            sprintf(text, "Hits_up(%c) before deleting %c", w->name, p->name);
            drawEvent(p, q, t, w->hitsUpRoot[dir]->parent,
            HITS_UP_TREE, dir, text, HORIZONTAL, &skip);
        }
        sprintf(text, "Hits_up(%c) before inserting %c", q->name, p->name);
        drawEvent(p, q, t, q->hitsUpRoot[dir]->parent,
        HITS_UP_TREE, dir, text, HORIZONTAL, &skip);

        insertS(q->hitsUpRoot[dir], p, HITS_UP_TREE, dir);

        sprintf(text, "Hits_up(%c) after inserting %c", q->name, p->name);
        drawEvent(p, q, t, q->hitsUpRoot[dir]->parent,
        HITS_UP_TREE, dir, text, HORIZONTAL, &skip);
    }

    vxp = getVx(p, dir);
    vxq = getVx(q, dir);

    aux = max(module(vxp), module(vxq));

    vxp -= aux;
    vxq -= aux;

    if(vxp < vxq - EPS) /* p is to the left */
        v = ownerS(p->cands[dir], CANDS_TREE, dir);
    else /* q is to the left */
        v = ownerS(q->cands[dir], CANDS_TREE, dir);

    if(v != NULL){
        sprintf(text, "Updating lcand(%c)", v->name);
        drawEvent(p, q, v, NULL,
        HITS_UP_TREE, dir, text, HORIZONTAL, &skip);
        change = updateLcand(v, dir);
        if(change) updateTourn(v, dir);
    }

    /* db(
        printf("Printing point %c\n", p->name);
        printPoint(p, dir);
        printf("Printing point %c\n", q->name);
        printPoint(q, dir);
    ); */
}

/* +60-order event */
void upEvent(Point * p, Point * q, int dir){
    HitsNode * auxh, *newHits;
    Point * v, *t;
    int change, skip = 1;
    char text[200];
    if(q == ownerS(p->hitsLow[dir], HITS_LOW_TREE, dir)){ /* p is in HitsLow(q) */
        db(
            if(dir == HORIZONTAL)
                printf("UP EVENT: case A, (%c, %c)\n", p->name, q->name);
        );
        v = ownerS(q->cands[dir], CANDS_TREE, dir); /* search for q in Cands(v) */
        if(v != NULL){
            sprintf(text, "Deleting %c from Cands(%c)", q->name, v->name);
            drawEvent(p, q, v, v->candsRoot[dir]->parent,
            CANDS_TREE, dir, text, UP, &skip);

            deleteS(v->candsRoot[dir], q, CANDS_TREE, dir);

            sprintf(text, "Cands(%c) after delete... updating lcand(%c)", v->name, v->name);
            drawEvent(p, q, v, v->candsRoot[dir]->parent,
            CANDS_TREE, dir, text, UP, &skip);
            /* check if some lcand changed */
            change = updateLcand(v, dir);
            if(change) updateTourn(v, dir);
        }

        /* check if some lcand changed */
        sprintf(text, "Inserting %c in Cands(%c)", q->name, p->name);
        drawEvent(p, q, v, p->candsRoot[dir]->parent,
        CANDS_TREE, dir, text, UP, &skip);

        insertS(p->candsRoot[dir], q, CANDS_TREE, dir);

        sprintf(text, "Cands(%c) after insert... updating lcand(%c)", p->name, p->name);
        drawEvent(p, q, v, p->candsRoot[dir]->parent,
        CANDS_TREE, dir, text, UP, &skip);

        change = updateLcand(p, dir);
        if(change) updateTourn(p, dir);

        auxh = (HitsNode *)successorS(q->hitsUpRoot[dir], p, HITS_UP_TREE, dir, HORIZONTAL);
        if(auxh != NULL)
            t = auxh->key;
        else
            t = ownerS(q->hitsLow[dir], HITS_LOW_TREE, dir);

        if(auxh != NULL){
            sprintf(text, "Extracting everyone to the left of %c", t->name);
            drawEvent(p, q, t, q->hitsUpRoot[dir]->parent,
            HITS_UP_TREE, dir, text, UP, &skip);
        }
        else{
            sprintf(text, "Extracting everyone");
            drawEvent(p, q, t, q->hitsUpRoot[dir]->parent,
            HITS_UP_TREE, dir, text, UP, &skip);
        }
        newHits = extractS(q->hitsUpRoot[dir], NULL, auxh, HITS_UP_TREE, dir);

        sprintf(text, "After extract");
        drawEvent(p, q, t, newHits,
        HITS_UP_TREE, dir, text, UP, &skip);

        newHits = joinS(detach(p->hitsUpRoot[dir], HITS_UP_TREE, dir), newHits, HITS_UP_TREE, dir);
        attach(p->hitsUpRoot[dir], newHits, HITS_UP_TREE, dir);

        sprintf(text, "After insert in Hits_up(%c)", p->name);
        drawEvent(p, q, t, p->hitsUpRoot[dir]->parent,
        HITS_UP_TREE, dir, text, UP, &skip);

        /* remove p from Hits_low(q) */
        sprintf(text, "Remove %c from Hits_low(%c)", p->name, q->name);
        drawEvent(p, q, p, q->hitsLowRoot[dir]->parent,
        HITS_LOW_TREE, dir, text, UP, &skip);
        deleteS(q->hitsLowRoot[dir], p, HITS_LOW_TREE, dir);
        sprintf(text, "After remove");
        drawEvent(p, q, p, q->hitsLowRoot[dir]->parent,
        HITS_LOW_TREE, dir, text, UP, &skip);

        if(t != NULL){
            sprintf(text, "Inserting %c in Hits_low(%c)", p->name, t->name);
            drawEvent(p, q, t, t->hitsLowRoot[dir]->parent,
            HITS_LOW_TREE, dir, text, UP, &skip);
            insertS(t->hitsLowRoot[dir], p, HITS_LOW_TREE, dir);
            sprintf(text, "After insert");
            drawEvent(p, q, t, t->hitsLowRoot[dir]->parent,
            HITS_LOW_TREE, dir, text, UP, &skip);
        }

    }
    else if(p == ownerS(q->cands[dir], CANDS_TREE, dir)){ /* q is in Cands(p) */
        db(
            if(dir == HORIZONTAL)
                printf("UP EVENT: case B, (%c, %c)\n", p->name, q->name);
        );
        t = ownerS(p->hitsLow[dir], HITS_LOW_TREE, dir);

        if(t != NULL){
            sprintf(text, "Deleting %c from Hits_low(%c)", p->name, t->name);
            drawEvent(p, q, t, t->hitsLowRoot[dir]->parent,
            HITS_LOW_TREE, dir, text, UP, &skip);
            deleteS(t->hitsLowRoot[dir], p, HITS_LOW_TREE, dir);
            sprintf(text, "After delete");
            drawEvent(p, q, t, t->hitsLowRoot[dir]->parent,
            HITS_LOW_TREE, dir, text, UP, &skip);
        }

        sprintf(text, "Insert %c in Hits_low(%c)", p->name, q->name);
        drawEvent(p, q, p, q->hitsLowRoot[dir]->parent,
        HITS_LOW_TREE, dir, text, UP, &skip);
        insertS(q->hitsLowRoot[dir], p, HITS_LOW_TREE, dir);
        sprintf(text, "After insert");
        drawEvent(p, q, p, q->hitsLowRoot[dir]->parent,
        HITS_LOW_TREE, dir, text, UP, &skip);

        auxh = (HitsNode *)predecessorS(p->hitsUpRoot[dir], q, HITS_UP_TREE, dir, UP);

        if(auxh != NULL)
            v = auxh->key;
        else
            v = ownerS(p->cands[dir], CANDS_TREE, dir);

        if(auxh != NULL){
            sprintf(text, "Extracting everyone to the right of %c", v->name);
            drawEvent(p, q, v, p->hitsUpRoot[dir]->parent,
            HITS_UP_TREE, dir, text, UP, &skip);
        }
        else{
            sprintf(text, "Extracting everyone");
            drawEvent(p, q, v, p->hitsUpRoot[dir]->parent,
            HITS_UP_TREE, dir, text, UP, &skip);
        }

        newHits = extractS(p->hitsUpRoot[dir], auxh, NULL, HITS_UP_TREE, dir);
        sprintf(text, "After extract");
        drawEvent(p, q, v, newHits,
        HITS_UP_TREE, dir, text, UP, &skip);
        newHits = joinS(newHits, detach(q->hitsUpRoot[dir], HITS_UP_TREE, dir), HITS_UP_TREE, dir);
        attach(q->hitsUpRoot[dir], newHits, HITS_UP_TREE, dir);

        sprintf(text, "After insert in Hits_up(%c)", q->name);
        drawEvent(p, q, v, q->hitsUpRoot[dir]->parent,
        HITS_UP_TREE, dir, text, UP, &skip);

        sprintf(text, "Deleting %c from Cands(%c)", q->name, p->name);
        drawEvent(p, q, v, p->candsRoot[dir]->parent,
        CANDS_TREE, dir, text, UP, &skip);

        deleteS(p->candsRoot[dir], q, CANDS_TREE, dir);
        sprintf(text, "After delete... updating lcand(%c)", p->name);
        drawEvent(p, q, v, p->candsRoot[dir]->parent,
        CANDS_TREE, dir, text, UP, &skip);

        /* check if some lcand changed */
        change = updateLcand(p, dir);
        if(change) updateTourn(p, dir);
        if(v != NULL){
            sprintf(text, "Inserting %c in Cands(%c)", q->name, v->name);
            drawEvent(p, q, v, v->candsRoot[dir]->parent,
            CANDS_TREE, dir, text, UP, &skip);
            insertS(v->candsRoot[dir], q, CANDS_TREE, dir);
            sprintf(text, "After insert... updating lcand(%c)", v->name);
            drawEvent(p, q, v, v->candsRoot[dir]->parent,
            CANDS_TREE, dir, text, UP, &skip);
            /* check if some lcand changed */
            change = updateLcand(v, dir);
            if(change) updateTourn(v, dir);
        }
    }

    // db(
    //     printf("Printing point %c\n", p->name);
    //     printPoint(p, dir);
    //     printf("Printing point %c\n", q->name);
    //     printPoint(q, dir);
    // );
}

/* -60-order event */
void downEvent(Point * p, Point * q, int dir){
    HitsNode * auxh, *newHits;
    Point * v, *t;
    int change, skip = 1;
    char text[200];

    if(q == ownerS(p->hitsUp[dir], HITS_UP_TREE, dir)){ /* p is in HitsUp(q) */
        db(
            if(dir == HORIZONTAL)
                printf("DOWN EVENT: case A, (%c, %c)\n", p->name, q->name);
        );
        v = ownerS(q->cands[dir], CANDS_TREE, dir); /* search for q in Cands(v) */
        if(v != NULL){
            sprintf(text, "Deleting %c from Cands(%c)", q->name, v->name);
            drawEvent(p, q, v, v->candsRoot[dir]->parent,
            CANDS_TREE, dir, text, DOWN, &skip);

            deleteS(v->candsRoot[dir], q, CANDS_TREE, dir);

            sprintf(text, "Cands(%c) after delete... updating lcand(%c)", v->name, v->name);
            drawEvent(p, q, v, v->candsRoot[dir]->parent,
            CANDS_TREE, dir, text, DOWN, &skip);
            /* check if some lcand changed */
            change = updateLcand(v, dir);
            if(change) updateTourn(v, dir);
        }

        sprintf(text, "Inserting %c in Cands(%c)", q->name, p->name);
        drawEvent(p, q, v, p->candsRoot[dir]->parent,
        CANDS_TREE, dir, text, DOWN, &skip);

        insertS(p->candsRoot[dir], q, CANDS_TREE, dir);

        sprintf(text, "After insert... updating lcand(%c)", p->name);
        drawEvent(p, q, v, p->candsRoot[dir]->parent,
        CANDS_TREE, dir, text, DOWN, &skip);
        /* check if some lcand changed */
        change = updateLcand(p, dir);
        if(change) updateTourn(p, dir);

        auxh = (HitsNode *)successorS(q->hitsLowRoot[dir], p, HITS_LOW_TREE, dir, HORIZONTAL);

        if(auxh != NULL)
            t = auxh->key;
        else
            t = ownerS(q->hitsUp[dir], HITS_UP_TREE, dir);

        if(auxh != NULL){
            sprintf(text, "Extracting everyone to the left of %c", t->name);
            drawEvent(p, q, t, q->hitsLowRoot[dir]->parent,
            HITS_LOW_TREE, dir, text, DOWN, &skip);
        }
        else{
            sprintf(text, "Extracting everyone");
            drawEvent(p, q, t, q->hitsLowRoot[dir]->parent,
            HITS_LOW_TREE, dir, text, DOWN, &skip);
        }

        newHits = extractS(q->hitsLowRoot[dir], NULL, auxh, HITS_LOW_TREE, dir);
        newHits = joinS(detach(p->hitsLowRoot[dir], HITS_LOW_TREE, dir), newHits, HITS_LOW_TREE, dir);
        attach(p->hitsLowRoot[dir], newHits, HITS_LOW_TREE, dir);

        sprintf(text, "After insert in Hits_low(%c)", p->name);
        drawEvent(p, q, t, p->hitsLowRoot[dir]->parent,
        HITS_LOW_TREE, dir, text, DOWN, &skip);

        sprintf(text, "Remove %c from Hits_up(%c)", p->name, q->name);
        drawEvent(p, q, t, q->hitsUpRoot[dir]->parent,
        HITS_UP_TREE, dir, text, DOWN, &skip);
        /* remove p from Hits_low(q) */
        deleteS(q->hitsUpRoot[dir], p, HITS_UP_TREE, dir);

        sprintf(text, "After remove");
        drawEvent(p, q, t, q->hitsUpRoot[dir]->parent,
        HITS_UP_TREE, dir, text, DOWN, &skip);

        if(t != NULL){
            sprintf(text, "Insert %c in Hits_up(%c)", p->name, t->name);
            drawEvent(p, q, t, t->hitsUpRoot[dir]->parent,
            HITS_UP_TREE, dir, text, DOWN, &skip);
            insertS(t->hitsUpRoot[dir], p, HITS_UP_TREE, dir);
            sprintf(text, "After insert");
            drawEvent(p, q, t, t->hitsUpRoot[dir]->parent,
            HITS_UP_TREE, dir, text, DOWN, &skip);
        }
    }
    else if(p == ownerS(q->cands[dir], CANDS_TREE, dir)){ /* q is in Cands(p) */
        db(
            if(dir == HORIZONTAL)
                printf("DOWN EVENT: case B, (%c, %c)\n", p->name, q->name);
        );
        t = ownerS(p->hitsUp[dir], HITS_UP_TREE, dir);

        if(t != NULL){
            sprintf(text, "Delete %c from Hits_up(%c)", p->name, t->name);
            drawEvent(p, q, t, t->hitsUpRoot[dir]->parent,
            HITS_UP_TREE, dir, text, DOWN, &skip);
            deleteS(t->hitsUpRoot[dir], p, HITS_UP_TREE, dir);
            sprintf(text, "After delete");
            drawEvent(p, q, t, t->hitsUpRoot[dir]->parent,
            HITS_UP_TREE, dir, text, DOWN, &skip);
        }
        sprintf(text, "Insert %c in Hits_up(%c)", p->name, q->name);
        drawEvent(p, q, t, q->hitsUpRoot[dir]->parent,
        HITS_UP_TREE, dir, text, DOWN, &skip);
        insertS(q->hitsUpRoot[dir], p, HITS_UP_TREE, dir);
        db(
            if(dir == HORIZONTAL){
                printf("New up(%c): %c\n", p->name, q->name);
                printf("Testing: up(%c) = %c\n", p->name,
                ownerS(p->hitsUp[dir], HITS_UP_TREE, dir)->name);
            }
        );
        sprintf(text, "After insert");
        drawEvent(p, q, t, q->hitsUpRoot[dir]->parent,
        HITS_UP_TREE, dir, text, DOWN, &skip);

        auxh = (HitsNode *)predecessorS(p->hitsLowRoot[dir], q, HITS_LOW_TREE, dir, DOWN);

        if(auxh != NULL)
            v = auxh->key;
        else
            v = ownerS(p->cands[dir], CANDS_TREE, dir);

        if(auxh != NULL){
            sprintf(text, "Extracting everyone to the right of %c", v->name);
            drawEvent(p, q, v, p->hitsLowRoot[dir]->parent,
            HITS_LOW_TREE, dir, text, DOWN, &skip);
        }
        else{
            sprintf(text, "Extracting everyone");
            drawEvent(p, q, v, p->hitsLowRoot[dir]->parent,
            HITS_LOW_TREE, dir, text, DOWN, &skip);
        }

        newHits = extractS(p->hitsLowRoot[dir], auxh, NULL, HITS_LOW_TREE, dir);
        newHits = joinS(newHits, detach(q->hitsLowRoot[dir], HITS_LOW_TREE, dir), HITS_LOW_TREE, dir);
        attach(q->hitsLowRoot[dir], newHits, HITS_LOW_TREE, dir);

        sprintf(text, "After insert in Hits_low(%c)", q->name);
        drawEvent(p, q, v, q->hitsLowRoot[dir]->parent,
        HITS_LOW_TREE, dir, text, DOWN, &skip);

        sprintf(text, "Remove %c from Cands(%c)", q->name, p->name);
        drawEvent(p, q, v, p->candsRoot[dir]->parent,
        CANDS_TREE, dir, text, DOWN, &skip);
        deleteS(p->candsRoot[dir], q, CANDS_TREE, dir);

        sprintf(text, "After delete... update lcand(%c)", p->name);
        drawEvent(p, q, v, p->candsRoot[dir]->parent,
        CANDS_TREE, dir, text, DOWN, &skip);
        change = updateLcand(p, dir);
        if(change) updateTourn(p, dir);
        if(v != NULL){
            sprintf(text, "Inserting %c in Cands(%c)", q->name, v->name);
            drawEvent(p, q, q, v->candsRoot[dir]->parent,
            CANDS_TREE, dir, text, DOWN, &skip);

            insertS(v->candsRoot[dir], q, CANDS_TREE, dir);

            sprintf(text, "After insert... updating lcand(%c)", v->name);
            drawEvent(p, q, q, v->candsRoot[dir]->parent,
            CANDS_TREE, dir, text, DOWN, &skip);
            change = updateLcand(v, dir);
            if(change) updateTourn(v, dir);
        }
    }

    // db(
    //     printf("Printing point %c\n", p->name);
    //     printPoint(p, dir);
    //     printf("Printing point %c\n", q->name);
    //     printPoint(q, dir);
    // );
}

/*
    The first certificate in the PQ has expired
*/
void event(){
    PQObject *aux;
    Point * p, *q, *r, *s;
    double a, b;
    int i;
    while(mod(valuePQ(1) - now) <= EPS){
        aux = minPQ();
        if(aux->certType >= TOURN_CERT){
            tournEvent();
            db(for(i = 2*tournElem - 1; i > 1; i -= 2){
                p = tourn[i]->p;
                q = tourn[i]->lcandp;
                r = tourn[i - 1]->p;
                s = tourn[i - 1]->lcandp;
                a = distance(p, q, tourn[i]->direction);
                b = distance(r, s, tourn[i - 1]->direction);
                if(a < b && mod(a - b) > EPS && tourn[i/2] != tourn[i]){
                    printf("%d and %d\n", i, i-1);
                    printf("%.8lf, %.8lf, %.8lf\n", tourn[i]->a, tourn[i]->b, tourn[i]->c);
                    exit(0);
                }
                else if(a > b && mod(a - b) > EPS && tourn[i/2] != tourn[i - 1]){
                    printf("%d and %d\n", i, i-1);
                    printf("%.8lf, %.8lf, %.8lf\n", tourn[i-1]->a, tourn[i-1]->b, tourn[i-1]->c);
                    exit(0);
                }
            });
        }
        else{
            listEvent(aux->p, aux->certType);
        }
    }
}