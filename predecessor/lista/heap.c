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

double valor(int i){
    return cert[Q[i]];
}

void altera_chavePQ(int i, double t){
    int j;
    j = indQ[i];
    cert[i] = t;
    int pai = j;
    while(pai/2 > 1 && valor(j) < valor(pai/2)){
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
        if(filho < m && valor(filho) > valor(filho + 1)) 
            filho += 1;
        if(valor(i) < valor(filho)) 
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

// Objeto * iniciaHeap(int n){
//     Objeto * array = (Objeto *)malloc((n + 1)*sizeof(Objeto));
//     return array;
// }

// void constroiHeap(Objeto * heap, int n, Bool maior){
//     int i;
     
//     for(i = n/2; i >= 1; i--)
//         peneira(i, n, heap, maior);
// }

// void peneira(int p, int n, Objeto * heap, Bool maior){
//     int c = 2*p;    
//     Objeto a = heap[p];
//     while(c <= n){
//         if(c < n && compara(heap+c, heap+c+1, maior)) c++;
//         if(compara(heap+c, &a, maior)) break;
//         if(!maior) (heap[c].posicao)->posicao = heap + p;
//         heap[p] = heap[c];                    
//         heap[p].indice = p;
//         p = c;
//         c = 2*p;
//     }
//     if(!maior) (a.posicao)->posicao = heap + p;
//     heap[p] = a;
//     heap[p].indice = p;        
// }

// void atualizaHeap(Objeto *heap, int n, int indice, double valor, Bool maior){    
//     Objeto a = heap[indice];
//     a.valor = valor;
//     while(indice > 1 && compara(heap + indice/2, &a, maior)){        
//         if(!maior) (heap[indice/2].posicao)->posicao = heap + indice;
//         heap[indice] = heap[indice/2];
//         heap[indice].indice = indice;
//         indice /= 2;
//     }    
//     if(!maior) (a.posicao)->posicao = heap + indice;
//     heap[indice] = a;
//     heap[indice].indice = indice;   

//     peneira(1, n, heap, maior);
// }