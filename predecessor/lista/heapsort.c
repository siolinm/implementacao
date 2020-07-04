#include"heapsort.h"

void peneiraHeap(int i, int m){
    int filho = 2*i + 1, pai = i;
    double x = valor(i);
    while(filho <= m){
        if(valor(filho) > valor(filho + 1)) 
            filho += 1;
        if(x <= valor(filho)) 
            break;
        sorted[pai] = sorted[filho];
        pai = filho;
        filho = 2*pai + 1;
    }
    sorted[pai] = i;
}

void heapsort(){
    int i, aux;

    for(i = n/2 - 1; i >= 0; i--)
        peneiraHeap(i, n-1);
    for(i = n - 1; i > 0; i--){
        /* sorted[0] e' o menor de todos (minHeap) */
        aux = sorted[i]; 
        sorted[i] = sorted[0]; 
        sorted[0] = aux;
        peneiraHeap(0, i-1);
    }
}