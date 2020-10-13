#include"maxima.h"

void initMaxima(int dir){
    maximaRoot = malloc(sizeof(*maximaRoot));
    maximaRoot->parent = NULL;
    maximaRoot->key = NULL;
    maximaRoot->left = maximaRoot->right = NULL;
    maximaRoot->leftmost = NULL;
}

void initializeCandsHits(int dir){
    int i;
    CandsNode * up, * low;
    initMaxima(dir);
    Point * p;
    heapsort(initial, dir);
    for(i = n; i >= 1; i--){
        p = initial[i];
        low = queryPredecessorCands(maximaRoot, p, UP, dir);
        up = querySuccessorCands(maximaRoot, p, DOWN, dir);

        /* inserts up(p) in HitsUp(p) */
        insertHits(p->hitsUpRoot[dir], up, dir);
        /* inserts low(p) in HitsLow(p) */
        insertHits(p->hitsLowRoot[dir], low, dir);
        /* stores Cands(p) */
        p->candsRoot[dir]->parent = extractCands(maximaRoot, low, up, dir);
        insertCands(maximaRoot, p, dir);
    }

    freeAllCands(maximaRoot);
}