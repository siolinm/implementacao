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
        db(
            printf("MAXIMA -- point %d\n", p->id); 
            printS(maximaRoot, CANDS_TREE);
        );
        low = predecessorS(maximaRoot, p, CANDS_TREE, dir, UP);         
        up = predecessorS(maximaRoot, p, CANDS_TREE, dir, DOWN); 

        /* inserts up(p) in HitsUp(p) */
        db(if(up){
            printf("Inserting %d in Hits_up(%d)\n", p->id, up->key->id);
        });
        if(up) insertS(up->key->hitsUpRoot[dir], p, HITS_UP_TREE, dir);
        /* inserts low(p) in HitsLow(p) */
        db(if(low){
            printf("Inserting %d in Hits_low(%d)\n", p->id, low->key->id);
        });
        if(low) insertS(low->key->hitsLowRoot[dir], p, HITS_LOW_TREE, dir);
        /* stores Cands(p) */
        aux = (CandsNode *)extractS(maximaRoot, low, up, CANDS_TREE, dir);
        db(
            printf("Cands(%d) = \n", p->id);
            printSR(aux, NULL, CANDS_TREE, 1, 0);
        );
        attach(p->candsRoot[dir], aux, CANDS_TREE, dir);
        db(
            printf("Inserting %d in MAXIMA\n", p->id);
        );
        insertS(maximaRoot, p, CANDS_TREE, dir);
        /*
            p->lcand[dir] = getLcand(p);
            insertTourn(p, dir);
        */
    }
    db(
        for(i = 1; i <= n; i++){            
            printPoint(initial[i], dir);        
        }
    );

    freeAllS(maximaRoot, CANDS_TREE);    
}