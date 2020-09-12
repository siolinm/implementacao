#include<stdlib.h>
#include<stdio.h>
#include"tempo.h"
#include"debug.h"
#ifndef _UTIL_H
#define _UTIL_H
#define max(a, b) ((a > b) ? a : b)
/*tamanho inicial da PQ*/
#define INITIAL_SIZE 100

/*
    Um elemento
*/
typedef struct Object
{
    int id;
    double speed;
    double initv;
    struct Object * next;
    struct Object * prev;
    double certificate;
    int pqpos;
    struct No * node;
} Object;

/*
    Um no da arvore
*/
typedef struct No
{
    struct No * left;
    struct No * right;
    struct Object * key;
    int height;
    int children;
} No;

/*
    quantidade total de elementos
*/
int n;

/*
    vetor para a fila de prioridade
*/
Object ** Q;

/*
    id do ultimo elemento nao adicionado
*/
int lastID;

/*
    raiz da arvore de ids
*/
No * root;

/*
    raiz da arvore de elementos
*/
No * raiz;

/*
    aloca os vetores assumindo que o numero de elementos e' m 
*/
void init(int m);

/* 
    libera a memoria alocada 
*/
void destroy();

/*
    destroi o objeto obj
*/
void destroyObject(Object * obj);

/*
    Troca o elemento i pelo elemento j na arvore e na lista ligada
*/
void swapObjects(Object * i, Object * j);

/*
    valor do objeto e no instante atual
*/
double value(Object * e);

/*
    Exibe a lista ligada (para debug)
*/
void printL();

typedef int Bool;

#endif