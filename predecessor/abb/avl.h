#include "util.h"
#ifndef _AVL_H
#define _AVL_H

/*
    Retorna a altura do no a, -1 se NULL;
*/
int altura(No *a);

/*
    Recalcula a altura do no a;
*/
void redefineAltura(No *a);

/*
    Cria um no com chave key;
*/
No *criaNo(Object *key);

/*
    Rotaciona o no para direita
*/
No *rotacionaDir(No *no);

/*
    Rotaciona o no para esquerda
*/
No *rotacionaEsq(No *no);

/*
    Retorna o balanco do no, que eh a diferenca entre a altura do filho esquerdo e a altura do filho direito
*/
int getBalance(No *no);

/*
    Insere recursivamente a chave na arvore e ajusta a lista ligada de chaves
*/
No *insereNo(No *raiz, Object *chave);

/*
    Retorna o menor elemento da arvore com raiz raiz
*/
No *menor(No *raiz);

/*
    Deleta recursivamente a chave da arvore e ajusta a lista ligada de chaves
*/
No *deleteNo(No *raiz, Object *chave);

/*
    Busca o k-esimo elemento na arvore recursivamente
*/
Object * queryKth(No *raiz, int i);

/*
    Exibe a arvore horizontalmente (para debug)
*/
void print(char * prefix, int size, No * r, int b);

/*
    desaloca toda memoria alocada
*/
void removeAll(No * raiz);

#endif