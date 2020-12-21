#include "kds.h"

void sendPoint(Point * p){
    int i;
    initial[lastID++] = p;

    p->id = lastID - 1;
    
    for(i = 0; i < 3; i++){        
        p->cands[i] = NULL;
        p->hitsLow[i] = NULL;
        p->hitsUp[i] = NULL;

        initS(p, CANDS_TREE, i);  
        initS(p, HITS_LOW_TREE, i);
        initS(p, HITS_UP_TREE, i);

        p->lastMatch[i] = -1;
        /* */
        p->listPosition[i] = NULL;
        p->next[i] = NULL;
        p->prev[i] = NULL;
        listInsert(p, i);
    }    
}

void initKDS(){
    initial = malloc((n + 1)*sizeof(*initial));
    lastID = 0;
    now = 0;
    listInit();
    initPQ();
}

void buildKDS(){
    initial[n] = initial[0];
    initial[0] = NULL;
    initMaxima(HORIZONTAL);
    initCandsHits(HORIZONTAL);
    /* initCertTourn() */
    /* buildTourn() */
    free(initial);
}

double nextEvent(){
    return minPQ()->p->cert[minPQ()->certType]->value;
}

void advance(double t){        
    if(t < now)
        printf("Time earlier than current time\n");
    
    while(t >= nextEvent()){
        now = nextEvent();
        event();
    }
    now = t;
}

void change(int j, Vector v){
   
}

void insert(Coordinate xt, Vector v){
    
}

void delete(int i){

}

void query(){    

}