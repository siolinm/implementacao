#include"pq.h"

#define pqpos(obj) obj->p->cert[obj->certType]->pqpos

void initPQ(){
    /* 3n from lists + 3n from tourn */    
    pqMaxSize = 6*n;
    Q = malloc(pqMaxSize*sizeof(*Q));
    pqSize = 0;
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

void insertPQ(Point * p, int certType){    
    PQObject * pq;
    resizePQ();

    pq = malloc(sizeof(*pq));
    pq->p = p;
    pq->certType = certType;
    
    Q[++pqSize] = pq;
    pqpos(pq) = pqSize;
    updatePQ(pq->p, pq->certType, valuePQ(pqSize));
}

void deletePQ(Point * p, int certType){
    PQObject * obj = Q[p->cert[certType]->pqpos];

    Q[pqpos(obj)] = Q[pqSize--];
    swim(pqpos(obj));
    sink(pqpos(obj), pqSize);
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

void updatePQ(Point * p, int certType, double t){
    PQObject * obj = Q[p->cert[certType]->pqpos];      
           
    p->cert[certType]->value = t;

    swim(pqpos(obj));
    sink(pqpos(obj), pqSize);
}

void swim(int i){
    PQObject * obj;
    double x;
    obj = Q[i];
    x = valuePQ(i);
    while(i/2 >= 1 && x < valuePQ(i/2)){
        Q[i] = Q[i/2];
        pqpos(Q[i/2]) = i;
        i = i/2;
    }
    Q[i] = obj;
    pqpos(obj) = i;
}

void sink(int i, int m){
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