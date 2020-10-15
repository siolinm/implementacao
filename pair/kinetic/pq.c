#include"pq.h"

#define pqpos(obj) obj->p->cert[obj->certType]->pqpos

void initPQ(){    
    /* 3n from lists + 3n from tourn */    
    pqMaxSize = 6*n;

    pqSize = 1;
}

void resizePQ(){
    int i;
    if(pqSize + 1 == pqMaxSize){
        PQObject ** W = malloc(2*pqMaxSize*sizeof(*W));
        
        for(i = 1; i <= pqSize; i++)
            W[i] = Q[i];
        
        free(Q);
        Q = W;
        pqMaxSize = 2*pqMaxSize;
    }
}

void insertPQ(PQObject * obj){    
    resizePQ();

    Q[++pqSize] = obj;
    pqpos(obj) = pqSize;
    updatePQ(obj, valuePQ(pqSize));
}

void deletePQ(PQObject * obj){
    int i = pqpos(obj);
    Q[i] = Q[pqSize--];
    sieve(i, pqSize);
}

PQObject * minPQ(){
    return Q[1];
}

double valueMinPQ(){
    return valuePQ(1);
}

double valuePQ(int i){    
    return Q[i]->p->cert[Q[i]->certType]->value;
}

double valuePQObject(PQObject * obj){
    return obj->p->cert[obj->certType]->value;
}

void updatePQ(PQObject * obj, double t){
    int p, j, type;
    double x;
    
    type = obj->certType;

    j = pqpos(obj);
    obj->p->cert[type]->value = t;

    p = j;
    x = valuePQ(j);
    while(p/2 >= 1 && x < valuePQ(p/2)){
        Q[p] = Q[p/2];
        pqpos(Q[p/2]) = p;
        p = p/2;
    }
    Q[p] = obj;
    pqpos(obj) = p;
    sieve(p, n);
}

void sieve(int i, int m){
    int s = 2*i, p = i;
    PQObject * x = Q[i];
    while(s <= m){
        if(s < m && valuePQ(s) > valuePQ(s + 1)) 
            s += 1;
        if(valuePQObject(x) < valuePQ(s)) 
            break;

        Q[p] = Q[s];
        pqpos(Q[p]) = p;        
        p = s; s = 2*p;
    }
    Q[p] = x;
    pqpos(x) = p;
}