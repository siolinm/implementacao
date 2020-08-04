#include"util.h"
#ifndef _QUERIES_H
#define _QUERIES_H

/*
    Arvore de acordo com os ids
*/

/*
    Busca pelo id 
*/
Object * queryQ(No * raiz, int id);

/*
    deleta a chave da arvore recursivamente e retorna uma nova raiz
*/
No *deleteNoQ(No *raiz, Object *chave);

/*
    insere a chave da arvore recursivamente e retorna uma nova raiz
*/
No *insereNoQ(No *raiz, Object *chave);

/*
    cria um no com chave key
*/
No *criaNoQ(Object *key);

/*
    exibe a arvore dos ids (para debug)
*/
void printQ(char * prefix, int size, No * r, int b);

/*
    desaloca toda memoria alocada
*/
void removeAllQ(No * raiz);

#endif