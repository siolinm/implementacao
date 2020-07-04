#include<stdio.h>
#include<stdlib.h>
#include"heap.h"
#include"util.h"

void initPQ(){
    int i;
    for(i = 1; i < n; i++)
        Q[i] = i;
    for(i = n/2; i >= 1; i--)
        peneira(i, n-1);
}

int minPQ(){
    return Q[1];
}

double value(int i){
    return cert[Q[i]];
}

void altera_chavePQ(int i, double t){
    int j;
    j = indQ[i];
    cert[i] = t;
    int pai = j;
    while(pai/2 > 1 && value(j) < value(pai/2)){
        Q[pai] = Q[pai/2];
        indQ[Q[pai/2]] = pai;        
        pai = pai/2;
    }
    Q[pai] = i;
    indQ[i] = pai;
    peneira(indQ[i], n-1);
}

void peneira(int i, int m){
    int filho = 2*i, pai = i;
    while(filho <= m){
        if(filho < m && value(filho) > value(filho + 1)) 
            filho += 1;
        if(value(i) < value(filho)) 
            break;
        /* 
            i desce, ou seja, filho sobe e 
            i e' o valor do pai novamente
        */
        Q[pai] = Q[filho];
        indQ[Q[filho]] = pai;        
        pai = filho; filho = 2*pai;
    }
    Q[pai] = i;
    indQ[i] = pai;
}