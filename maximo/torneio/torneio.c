#include"torneio.h"

Objeto ** criaTorneio(int n){
    int i;
    /* 1 ate 2n-1 */
    Objeto ** torneio = (Objeto **)malloc(2*n*sizeof(Objeto *));
    for(i = 2*n - 1; i >= n; i--) torneio[i] = (Objeto *)malloc(sizeof(Objeto));
    return torneio;
}

void simulaRodada(Objeto ** torneio, Objeto * heapCert, int lastPos, int size){
    int i;
    if(size == 1) return;
    for(i = size; i > lastPos; i--){        
        if(i-1 > lastPos) 
            i--;
        else            
            break;        
        if(compara(torneio[i], torneio[i+1], 0)){
            torneio[i/2] = torneio[i];
            torneio[i+1]->indice = i+1;
            criaCertificado(torneio, heapCert, torneio[i+1], torneio[i]);
        }
        else{
            torneio[i/2] = torneio[i+1];        
            torneio[i]->indice = i;
            criaCertificado(torneio, heapCert, torneio[i], torneio[i+1]);
        }
    }    
    size = lastPos + ((size-lastPos)%2);
    lastPos = lastPos/2;
    simulaRodada(torneio, heapCert, lastPos, size);
}

void freeTorneio(Objeto ** torneio, int n){
    int i;
    for(i = 2*n -1; i >= n; i--){
        free(torneio[i]);
    }
    free(torneio);
}