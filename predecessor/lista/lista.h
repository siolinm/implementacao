#ifndef _LISTA_H
#define _LISTA_H
#include"util.h"
#include"time.h"
#include"certificados.h"
#include<stdio.h>

Objeto * criaLista(int n);

void predecessor(int i);

int compare(const void * a, const void * b);



#endif