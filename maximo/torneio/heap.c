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
        if(!maior) (heap[p].posicao)->posicao = heap + p;
        heap[p] = heap[c];        
        heap[p].indice = p;        
        p = c;
        c = 2*p;
    }
    if(!maior) (a.posicao)->posicao = heap + p;
    heap[p] = a;    
    heap[p].indice = p;
}

void atualizaHeap(Objeto *heap, int n, int indice, double valor, Bool maior){
    /* melhorar depois */
    Objeto a = heap[indice];
    a.valor = valor;
    while(indice > 1 && compara(heap + indice/2, &a, maior)){
        (heap[indice/2].posicao)->posicao = heap + indice;
        heap[indice] = heap[indice/2];
        heap[indice].indice = indice/2;
        indice /= 2;
    }
    (a.posicao)->posicao = heap + indice;
    heap[indice] = a;    
    heap[indice].indice = indice;

    peneira(1, n, heap, maior);
}