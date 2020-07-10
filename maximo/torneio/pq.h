#include<stdio.h>
#include<stdlib.h>
#include"util.h"
#include"debug.h"
#ifndef _HEAP_H
#define _HEAP_H

/*
    Inicializa a fila de prioridade
*/
void initPQ();

/*
    devolve o certificado com 
    menor valor da fila de prioridade
*/
int minPQ();

/*
    Devolver o valor do certificado que 
    esta na posicao i da fila de prioridade
*/
double value(int i);

/*
    Ajusta o valor do i-esimo certificado para t
    e ajusta a PQ de acordo
*/
void altera_chavePQ(int i, double t);

/*
    Garante a propriedade do heap "descendo"/"peneirando"
    os elementos
*/
void peneira(int i, int m);

#endif