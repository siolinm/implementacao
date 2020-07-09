#include"heap.h"
#include"util.h"

void peneiraHeap(int i, int m){
    int filho = 2*i, pai = i;
    double x = valor(i);
    i = heap[i];
    while(filho <= m){
        if(filho < m && valor(filho) < valor(filho + 1)) 
            filho += 1;
        if(x >= valor(filho)) 
            break;
        heap[pai] = heap[filho];
        indH[heap[filho]] = pai;
        pai = filho;
        filho = 2*pai;
    }
    heap[pai] = i;
    indH[i] = pai;
}

void initHeap(){
    int i;    

    for(i = n/2; i >= 1; i--)
        peneiraHeap(i, n);
    
}