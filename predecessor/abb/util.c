#include"util.h"
#include"tempo.h"

void init(int m){
    n = m;
    Q = malloc((n + 1)*sizeof(*Q));
}

void destroy(){
    free(Q);
}

void destroyObject(Object * a){
    free(a);
}

double value(Object * e){
    return e->initv + e->speed*getTime();
}

void swapObjects(Object * a, Object * b){
    Object * c, *d;
    No * noa = a->node;
    No * nob = b->node;
    noa->key = b;
    nob->key = a;

    c = b->next;
    d = b->prev;

    b->next = a->next;
    b->prev = a->prev;
    a->next = c;
    a->prev = d;
}