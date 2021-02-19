#include"maxima.h"
#include"debug.h"

void initMaxima(int dir){
    maximaRoot = malloc(sizeof(*maximaRoot));
    maximaRoot->parent = NULL;
    maximaRoot->key = NULL;
    maximaRoot->left = maximaRoot->right = NULL;
    maximaRoot->leftmost = NULL;
}

void initCandsHits(int dir){
    int i;
    CandsNode * up, * low, *aux;
    Point * p;
    
    initMaxima(dir);
    heapsort(initial, dir);

    for(i = 1; i <= n; i++){
        p = initial[i];
        /* db(
            printf("MAXIMA -- point %c\n", p->name); 
            printS(maximaRoot, CANDS_TREE);
        ); */
        low = predecessorS(maximaRoot, p, CANDS_TREE, dir, DOWN);         
        up = predecessorS(maximaRoot, p, CANDS_TREE, dir, UP); 

        /* inserts up(p) in HitsUp(p) */
        /* db(if(up){
            printf("Inserting %c in Hits_up(%c)\n", p->name, up->key->name);
        }); */
        if(up) insertS(up->key->hitsUpRoot[dir], p, HITS_UP_TREE, dir);
        /* inserts low(p) in HitsLow(p) */
        /* db(if(low){
            printf("Inserting %c in Hits_low(%c)\n", p->name, low->key->name);
        }); */
        if(low) insertS(low->key->hitsLowRoot[dir], p, HITS_LOW_TREE, dir);
        /* stores Cands(p) */
        aux = (CandsNode *)extractS(maximaRoot, low, up, CANDS_TREE, dir);
        /* db(
            printf("Cands(%c) = \n", p->name);
            printSR(aux, NULL, CANDS_TREE, 1, 0);
        ); */
        attach(p->candsRoot[dir], aux, CANDS_TREE, dir);
        /* db(
            printf("Inserting %c in MAXIMA\n", p->name);
        ); */
        insertS(maximaRoot, p, CANDS_TREE, dir);
        
        updateLcand(p, dir);               
        
    }
    /* db(
        for(i = 1; i <= n; i++){            
            printPoint(initial[i], dir);        
        }
    ); */

    freeAllS(getParentS(maximaRoot, CANDS_TREE), CANDS_TREE, dir);
    free(maximaRoot);
}