#include<stdlib.h>
#include<stdio.h>
#include"tempo.h"
#include"debug.h"
#ifndef _UTIL_H
#define _UTIL_H
#define max(a, b) ((a > b) ? a : b)
#define INITIAL_SIZE 100
/*
typedef struct Certificate
{
    int id;
    double value;
    int pos;
} Certificate;
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

No * root;

No * raiz;

/*
    aloca os vetores assumindo que o numero de elementos e' m 
*/
void init();

/* 
    libera a memoria alocada 
*/
void destroy();

/*
    destroi o objeto obj
*/
void destroyObject(Object * obj);

/*
    Troca o elemento i pelo elemento j na arvore
*/
void swapObjects(Object * i, Object * j);

double value(Object * e);

void printL();

typedef int Bool;

#endif