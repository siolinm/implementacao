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
        heap[i].indice = i;    
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
        if(!maior) (*(heap[c].posicao)).posicao = heap + p;
        heap[p] = heap[c];        
        heap[p].indice = p;        
        p = c;
        c = 2*p;
    }
    if(!maior) (*(a.posicao)).posicao = heap + p;
    heap[p] = a;    
    heap[p].indice = p;
}

void atualizaHeap(Objeto *heap, int n, int posicao, double valor, Bool maior){
    /* melhorar depois */
    Objeto a = heap[posicao];
    a.valor = valor;
    while(posicao > 1 && compara(heap + posicao/2, &a, maior)){
        (*(heap[posicao/2].posicao)).posicao = heap + posicao;
        heap[posicao] = heap[posicao/2];
        heap[posicao].indice = posicao/2;
        posicao /= 2;
    }
    (*(a.posicao)).posicao = heap + posicao;
    heap[posicao] = a;    
    heap[posicao].indice = posicao;

    peneira(1, n, heap, maior);
}