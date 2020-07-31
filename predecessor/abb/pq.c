#include<stdio.h>
#include<stdlib.h>
#include"util.h"
#include"debug.h"
#include"pq.h"
int m = 0;
int maxsize = INITIAL_SIZE;

void initPQ(){
    int i;
    m = n;

    for(i = m/2; i >= 1; i--){
        peneira(i, m);             
    }
}

void insertPQ(Object * obj){
    int i;
    if(m + 1 == maxsize){
        Object ** W = malloc(2*maxsize*sizeof(*W));
        for(i = 1; i <= m; i++)
            W[i] = Q[i];
        
        free(Q);
        Q = W;
        maxsize = 2*maxsize;
    }
    Q[++m] = obj;
    obj->pqpos = m;
    updatePQ(obj, obj->certificate);
}

void deletePQ(Object * obj){
    int i = obj->pqpos;
    Q[i] = Q[m--];
    peneira(i, m);
}

Object * minPQ(){
    return Q[1];
}

double valor(int i){
    return Q[i]->certificate;
}

void updatePQ(Object * obj, double t){
    int pai, j;
    double x;
    obj->certificate = t;
    j = obj->pqpos;
    pai = j;
    x = valor(j);
    while(pai/2 >= 1 && x < valor(pai/2)){
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
        if(filho < m && valor(filho) > valor(filho + 1)) 
            filho += 1;
        if(x->certificate < valor(filho)) 
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

void printPQ(char * prefix, int size, int idx, int b){
	int i;
    char * novo;
    if(prefix == NULL){
        prefix = malloc(sizeof(*prefix));
        prefix[0] = '\0';
    }
    if(idx <= m)
    {
        for(i = 0; prefix[i] != '\0'; i++)
            printf("%c", prefix[i]);

        if(b) 
            printf("├──"); 
        else 
            printf("└──" );
        /*printf("%d: %g*t + %g = %g\n", Q[idx]->id, Q[idx]->speed, Q[idx]->initv, value(Q[idx]));*/
        printf("%g\n", Q[idx]->certificate);        
		
        novo = malloc((size + 4)*sizeof(*novo));
        for(i = 0; i < size; i++)
            novo[i] = prefix[i];
        if(b)
            novo[size - 1] = '|';
        else
            novo[size - 1] = ' ';
        for(i = size; i < size + 4; i++)
            novo[i] = ' ';        
        novo[size + 3] = '\0';
		printPQ(novo, size + 4, 2*idx, 1);
        printPQ(novo, size + 4, 2*idx + 1, 0);
        
    }
    if(!b)
        free(prefix);
}