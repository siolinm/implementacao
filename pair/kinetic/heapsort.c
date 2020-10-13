#include"heapsort.h"

double valueHeapsort(Point **v, int i, int dir){
    return getX(v[i], dir);
}

int compare(Point **v, int i, int j, int dir){
    return (valueHeapsort(v, i, dir) > valueHeapsort(v, j, dir));
}

void swapHeapsort(int i, int j, Point ** v){
    Point **aux;
    aux = v[i];
    v[i] = v[j];
    v[j] = aux;
}

void sieveHeap(Point **v, int i, int m, int dir){
    int s = 2*i, p = i;
    double x = valueHeapsort(v, i, dir);
    Point * aux = v[i];

    while(s <= m){
        if(s < m && compare(v, s, s + 1, dir)) 
            s += 1;
        if(x < valueHeapsort(v, s, dir))
            break;
        v[p] = v[s];
        
        p = s;
        s = 2*p;
    }

    v[p] = aux;
    
}

void heapsort(Point ** v, int dir){
    int i;

    for(i = n/2; i >= 1; i--){
        sieveHeap(v, i, n, dir);
    }

    for(i = n; i > 1; i--){        
        swapHeapsort(1, i, v);
        sieveHeap(v, 1, i-1, dir);
    }
}