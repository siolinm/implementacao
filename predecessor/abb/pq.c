#include<stdio.h>
#include<stdlib.h>
#include"util.h"
#include"debug.h"
int m = 0;
int maxsize = 100;

void initPQ(){
    int i;
    m = n;

    for(i = m/2; i >= 1; i--){
        peneira(i, m);             
    }
}

void insertPQ(Object * obj){
    if(m + 1 == maxsize){
        Object ** W = malloc(2*maxsize*sizeof(*W));
        for(int i = 1; i <= m; i++)
            W[i] = Q[i];
        
        free(Q);
        Q = W;
        maxsize = 2*maxsize;
    }
    Q[++m] = obj;
    updatePQ(m, obj->certificate);
}

void deletePQ(Object * obj){
    int i = obj->pqpos;
    Q[i] = Q[m--];
    peneira(i, m);
}

int minPQ(){
    return Q[1];
}

double value(int i){
    return Q[i]->certificate;
}


void updatePQ(Object * obj, double t){
    int pai, j;
    double x;
    obj->certificate = t;
    j = obj->pqpos;    
    pai = j;
    x = value(j);
    while(pai/2 >= 1 && x < value(pai/2)){
        Q[pai] = Q[pai/2];
        Q[pai/2]->pqpos = pai;        
        pai = pai/2;
    }
    Q[pai] = obj;
    obj->pqpos = pai;
    peneira(pai, m);
}

void peneira(int i, int m){
    int filho = 2*i, pai = i;
    Object * x = Q[i];
    while(filho <= m){
        if(filho < m && value(filho) > value(filho + 1)) 
            filho += 1;
        if(x->certificate < value(filho)) 
            break;
        /* 
            i desce, ou seja, filho sobe e 
            i e' o valor do pai novamente
        */
        Q[pai] = Q[filho];
        Q[pai]->pqpos = pai;        
        pai = filho; filho = 2*pai;
    }
    Q[pai] = x;
    x->pqpos = pai;
}


