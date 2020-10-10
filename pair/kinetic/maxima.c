#include"maxima.h"

#define minimum(a, b, dir) (getX(a, dir) > getX(b, dir) ? b : a)

void initMaxima(int dir){
    maximaRoot = NULL;
}

CandsNode * queryUp(CandsNode * root, int dir){

}

CandsNode * queryLow(CandsNode * root, int dir){

}

/* searchs for up/low(p) in the tree with root root and returns a subtree containing all nodes above/beside*/
CandsNode * extractCands(CandsNode * root, CandsNode * up, CandsNode * low, int dir){
    /* atualizar maximaRoot */
}

void attachCands(CandsNode * candsRoot, Item * p){

}

void initializeCandsHits(int dir){
    int i;
    CandsNode * up, * low;
    initMaxima(dir);
    Point * p;    
    heapsort(initial, dir);
    for(i = 0; i < n; i++){
        p = initial[i];
        up = queryUp(maximaRoot, dir);
        low = queryLow(maximaRoot, dir);

        insertHits(up);
        insertHits(low);

        maximaRoot = insertCands(p);
    }

    freAll(maximaRoot);
}