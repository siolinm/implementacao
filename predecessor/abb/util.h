#include<stdlib.h>
#include<stdio.h>
#ifndef _UTIL_H
#define _UTIL_H
#define max(a, b) ((a > b) ? a : b)

typedef struct Certificate
{
    int id;
    double value;
    int pos;
} Certificate;

typedef struct Object
{
    int id;
    double speed;
    double initv;
    Object * next;
    Object * prev;
    No * node;
} Object;

typedef struct No
{
    No * left;
    No * right;
    Object * key;
    int height;
    int less;
} No;


/*
    quantidade total de elementos
*/
int n;

/*
    vetor para a fila de prioridade
*/
int * Q;

/*
    id do ultimo elemento adicionado
*/
int lastID;

/*
    aloca os vetores assumindo que o numero de elementos e' m 
*/
void init();

/* 
    libera a memoria alocada 
*/
void destroy();

/*
    Retorna o valor do i-esimo ponto em sorted
*/
double valor(Object * e);

/*
    Troca o elemento i pelo elemento j na arvore
*/
void swap(Object * i, Object * j);

typedef int Bool;

#endif