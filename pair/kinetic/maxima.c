#include"maxima.h"

void initMaxima(int dir){
    maximaRoot = malloc(sizeof(*maximaRoot));
    maximaRoot->parent = NULL;
    maximaRoot->key = NULL;
    maximaRoot->left = maximaRoot->right = NULL;
    maximaRoot->leftmost = NULL;
}

void initCandsHits(int dir){
    int i;
    CandsNode * up, * low;
    Point * p;
    initMaxima(dir);
    heapsort(initial, dir);
    for(i = n; i >= 1; i--){
        p = initial[i];
        low = queryPredecessorCands(maximaRoot, p, UP, dir);
        up = querySuccessorCands(maximaRoot, p, DOWN, dir);

        /* inserts up(p) in HitsUp(p) */
        if(up) insertHits(p->hitsUpRoot[dir], up->key, dir, 1);
        /* inserts low(p) in HitsLow(p) */
        if(low) insertHits(p->hitsLowRoot[dir], low->key, dir, 0);
        /* stores Cands(p) */
        p->candsRoot[dir]->parent = extractCands(maximaRoot, low, up, dir);
        insertCands(maximaRoot, p, dir);
    }

    freeAllCands(maximaRoot);    
}