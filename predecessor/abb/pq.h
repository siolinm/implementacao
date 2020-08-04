#include"util.h"
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
Object * minPQ();

/*
    Devolver o valor do certificado que 
    esta na posicao i da fila de prioridade
*/
double valor(int i);

/*
    Ajusta o valor do certificado do objeto c para t
    e ajusta a PQ de acordo
*/
void updatePQ(Object * c, double t);

/*
    Garante a propriedade do heap "descendo"/"peneirando"
    os elementos
*/
void peneira(int i, int m);

/*
    insere o objeto obj na PQ
*/
void insertPQ(Object * obj);

/*
    remove o objeto obj da PQ
*/
void deletePQ(Object * obj);

/*
    exibe a PQ (para debug)
*/
void printPQ(char * prefix, int size, int idx, int b);
#endif