#include"util.h"
#ifndef _AVL_H
#define _AVL_H

typedef struct No
{
    Objeto * chave;
    No* esq;
    No* dir;
    int alt;
} No;

int altura(No * a);

#endif