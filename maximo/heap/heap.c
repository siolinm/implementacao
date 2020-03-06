#include<stdio.h>
#include<stdlib.h>
#include"heap.h"
#include"util.h"

Objeto * iniciaHeap(int n){
    Objeto * array = (Objeto *)malloc((n + 1)*sizeof(Objeto));
    return array;
}

void constroiHeap(Objeto * heap, int n, Bool maior){
    int i;
    if(maior)
    for(i = 1; i <= n; i++){        
        heap[i].valor = heap[i].traj.b;    
        heap[i].index = i;    
    } 
    for(i = n/2; i >= 1; i--)
        peneira(i, n, heap, maior);
}

void peneira(int p, int n, Objeto * heap, Bool maior){
    int c = 2*p;    
    Objeto a = heap[p];
    while(c <= n){
        if(c < n && compara(heap+c, heap+c+1, maior)) c++;
        if(compara(heap+c, &a, maior)) break;
        /* melhorar isso */
        if(!maior) (*(heap[c].indice)).indice = heap + p;
        heap[p] = heap[c];        
        heap[p].index = p;        
        p = c;
        c = 2*p;
    }
    if(!maior) (*(a.indice)).indice = heap + p;
    heap[p] = a;    
    heap[p].index = p;
}

void atualizaHeap(Objeto *heap, int n, int indice, double valor, Bool maior){
    /* melhorar depois */
    Objeto a = heap[indice];
    a.valor = valor;
    while(indice > 1 && compara(heap + indice/2, &a, maior)){
        (*(heap[indice/2].indice)).indice = heap + indice;
        heap[indice] = heap[indice/2];
        heap[indice].index = indice/2;
        indice /= 2;
    }
    (*(a.indice)).indice = heap + indice;
    heap[indice] = a;    
    heap[indice].index = indice;

    peneira(1, n, heap, maior);
}