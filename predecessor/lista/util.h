#include<stdlib.h>
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


// typedef struct Trajetoria
// {
//     double x0;
//     double velocidade;
// } Trajetoria;

// enum{
//     PONTO,
//     CERTIFICADO
// };

// typedef struct Elemento
// {

// };

// typedef struct Objeto
// {
//     Trajetoria traj;
//     double valor;
//     /* ponteiro para o objeto correspondente (certificado-ponto menor)
//      */
//     struct Objeto * posicao;
//     /* posicao em que o objeto se encontra no vetor do heap */
//     int indice;    
// } Objeto;

// typedef struct Certificado
// {
    
// };



typedef int Bool;

/* Funcao para comparar a e b de acordo com o parametro maior. Se maior = 1, retorna true caso a <= b.
    Se maior = 0, retorna true caso a >= b.
*/
// Bool compara(Objeto * a, Objeto * b, Bool maior);

// /* Troca o conteudo de a com o de b */
// void swap(Objeto * a, Objeto * b);

#endif