#include"heapsort.h"
#include"util.h"

void peneiraHeap(int i, int m){
    int filho = 2*i, pai = i;
    double x = valor(i);
    i = sorted[i];
    while(filho <= m){
        if(filho < m && valor(filho) > valor(filho + 1)) 
            filho += 1;
        if(x <= valor(filho)) 
            break;
        sorted[pai] = sorted[filho];
        pai = filho;
        filho = 2*pai;
    }
    sorted[pai] = i;
}

void heapsort(){
    int i, aux;    

    for(i = n/2; i >= 1; i--){
        peneiraHeap(i, n);
    }
    for(i = n; i > 1; i--){
        /* sorted[0] e' o menor de todos (minHeap) */
        aux = sorted[i]; 
        sorted[i] = sorted[1]; 
        sorted[1] = aux;
        peneiraHeap(1, i-1);
    }
}