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
        indS[sorted[filho]] = pai;
        pai = filho;
        filho = 2*pai;
    }
    sorted[pai] = i;
    indS[i] = pai;
}

void heapsort(){
    int i;    

    for(i = n/2; i >= 1; i--){
        peneiraHeap(i, n);
    }
    for(i = n; i > 1; i--){
        /* sorted[0] e' o menor de todos (minHeap) */
        swapSorted(1, i);
        peneiraHeap(1, i-1);
    }
}