#include"heapsort.h"
#include"util.h"

double valor(int i){
    return getXCoordinate(points[i]);
}

void sieve(int i, int m){
    Point * aux = points[i];
    int filho = 2*i, pai = i;
    double x = valor(i);
    while(filho <= m){
        if(filho < m && valor(filho) < valor(filho + 1)) 
            filho += 1;

        if(x >= valor(filho))
            break;
        points[pai] = points[filho];        
        pai = filho;
        filho = 2*pai;
    }
    points[pai] = aux;
}

void heapsort(){
    int i;

    for(i = n/2; i >= 1; i--)
        sieve(i, n);
    
    for(i = n; i > 1; i--){     
        swapPoints(1, i);
        sieve(1, i-1);
    }
}