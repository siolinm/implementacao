#include<stdlib.h>
#include<stdio.h>
#ifndef _UTIL_H
#define _UTIL_H
#define max(a, b) ((a > b) ? a : b)

/*
    cert[i] guarda o certificado entre i/2 e i (um valor que indica seu vencimento)
*/
double * cert;

/*
    speed[i] e' a velocidade do i-esimo elemento
*/
double * speed;

/*
    x0[i] e' o valor inicial do i-esimo elemento
*/
double * x0;

/*
    heap[i] e' o indice do elemento que se encontra na i-esima posicao de acordo com o seu valor 
    (maxHeap).
*/
int * heap;

/*
    fila de prioridade que contem os certificados. Q[1] e' o indice do certificado com chave t minima
*/
int * Q;

/*
    indQ[i] e' a posicao do i-esimo certificado na fila de prioridade Q;
*/
int * indQ;

/*
    indH[i] e' a posicao em heap do i-esimo elemento da entrada
*/
int * indH;

/*
    quantidade total de elementos
*/
int n;

/*
    aloca os vetores assumindo que o numero de elementos e' m 
*/
void init(int m);

/* 
    libera a memoria alocada 
*/
void destroy();


/*
    Retorna o valor da i-esima posicao em heap
*/
double valor(int i);

/*
    Troca o i-esimo elemento de heap pelo j-esimo
*/
void swapheap(int i, int j);

typedef int Bool;

void printH();

void printC();

void printPQ();

void printIQ();

void printIH();

#endif