#include"heap.h"
#include"util.h"

void sieveHeap(int i, int m){
    int s = 2*i, p = i;
    double x = value(i);
    i = heap[i];
    
    while(s <= m){
        if(s < m && value(s) < value(s + 1)) 
            s += 1;
        if(x >= value(s)) 
            break;

        heap[p] = heap[s];
        indH[heap[s]] = p;
        p = s;
        s = 2*p;
    }
    heap[p] = i;
    indH[i] = p;
}

void initHeap(){
    int i;    

    for(i = n/2; i >= 1; i--)
        sieveHeap(i, n);
    
}