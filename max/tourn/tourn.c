#include"tourn.h"

void initTourn(){
    int i = 2*n - 1;
    while(i > 1){
        if(tourn[i] > tourn[i - 1]){
            tourn[i/2] = tourn[i];
            indT[tourn[i - 1]] = i - 1;
        }
        else{
            tourn[i/2] = tourn[i - 1];
            indT[tourn[i]] = i;
        }

        i = i - 2;
    }
}