#ifndef _QUERIES_H
#define _QUERIES_H

No * root = NULL;

Object * queryQ(No * raiz, int id);

No *deleteNoQ(No *raiz, Object *chave);

No *insereNoQ(No *raiz, Object *chave);

#endif