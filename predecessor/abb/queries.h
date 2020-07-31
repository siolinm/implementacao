#include"util.h"
#ifndef _QUERIES_H
#define _QUERIES_H

Object * queryQ(No * raiz, int id);

No *deleteNoQ(No *raiz, Object *chave);

No *insereNoQ(No *raiz, Object *chave);

No *criaNoQ(Object *key);

void printQ(char * prefix, int size, No * r, int b);

#endif