#include "listapontos.h"

void resize(int newSize){
    Objeto ** novoArray;
    maxSize = newSize;
    novoArray = malloc(maxSize*sizeof(Objeto *));
}

void inserePonto(Objeto * ponto){
    if(nPontos == maxSize) resize(2*(maxSize + 1));
    listaPontos[nPontos++] = ponto;    
}

Objeto * getPonto(int i){
    return listaPontos[i];
}

void predecessor(int i){
    Objeto * ponto = listaPontos[i]->predecessor;
    printf("O predecessor de %lf*t + %lf e ", listaPontos[i]->traj.a, listaPontos[i]->traj.b);
    printf("%lf*t + %lf\n", ponto->traj.a, ponto->traj.b);
}