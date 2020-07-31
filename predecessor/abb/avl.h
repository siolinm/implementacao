#include "util.h"
#ifndef _AVL_H
#define _AVL_H

No *raiz = NULL;

int altura(No *a);

void redefineAltura(No *a);

No *criaNo(Object *key);

No *rotacionaDir(No *no);

No *rotacionaEsq(No *no);

int getBalance(No *no);

No *insereNo(No *raiz, Object *chave);

No *menor(No *raiz);

No *deleteNo(No *raiz, Object *chave);

Object * queryKth(No *raiz, int i);

#endif