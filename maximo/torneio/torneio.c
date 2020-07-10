#include"torneio.h"

void initTorneio(){
    int i = 2*n - 1;
    while(i > 1){
        if(torneio[i] > torneio[i - 1]){
            torneio[i/2] = torneio[i];
            indT[torneio[i - 1]] = i - 1;
        }
        else{
            torneio[i/2] = torneio[i - 1];
            indT[torneio[i]] = i;
        }

        i = i - 2;
    }
}