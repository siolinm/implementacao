#include<stdlib.h>
#include<stdio.h>
#ifndef _UTIL_H
#define _UTIL_H
#define max(a, b) ((a > b) ? a : b)

/*
    cert[i] guarda o certificado entre i e i + 1 (um valor que indica seu vencimento)
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
    sorted[i] e' o indice do elemento que se encontra na i-esima posicao de acordo com o seu valor 
    (sorted esta ordenado decrescentemente).
*/
int * sorted;

/*
    fila de prioridade que contem os certificados. Q[1] e' o indice do certificado com chave t minima
*/
int * Q;

/*
    indQ[i] e' a posicao do i-esimo certificado na fila de prioridade Q;
*/
int * indQ;

/*
    indS[i] e' a posicao em sorted do i-esimo elemento da entrada
*/
int * indS;

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
    Retorna o valor do i-esimo ponto em sorted
*/
double valor(int i);

/*
    Troca o i-esimo elemento de sorted pelo j-esimo
*/
void swapSorted(int i, int j);

typedef int Bool;

void printS();

void printC();

void printPQ();

void printIQ();

void printIS();

#endif