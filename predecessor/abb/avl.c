#include "avl.h"
/*
    https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
    https://www.geeksforgeeks.org/avl-tree-set-2-deletion/
    https://www.youtube.com/watch?v=YkF76cOgtMQ&list=PLxI8Can9yAHf8k8LrUePyj0y3lLpigGcl&index=21
    https://www.youtube.com/watch?v=FzS0n_Z8lrk
*/

No *raiz = NULL;

int altura(No *a)
{
    return (a ? a->alt : -1);
}

void redefineAltura(No *a)
{
    a->alt = max(alt(a->esq), alt(a->dir)) + 1;
}

No *criaNo(Objeto *chave)
{
    No *novo = (No *)malloc(sizeof(No));

    novo->esq = NULL;
    novo->dir = NULL;
    novo->chave = chave;
    novo->alt = 1;

    return novo;
}

No *rotacionaDir(No *no)
{
    No *filhoEsq, *aux;

    filhoEsq = no->esq;
    if (!filhoEsq)
        return no;
    aux = filhoEsq->dir;

    filhoEsq->dir = no;
    no->esq = aux;

    redefineAltura(no);
    redefineAltura(filhoEsq);

    return filhoEsq;
}

No *rotacionaEsq(No *no)
{
    No *filhoDir, *aux;

    filhoDir = no->dir;
    if (!filhoDir)
        return no;
    aux = filhoDir->esq;

    filhoDir->esq = no;
    no->dir = aux;

    redefineAltura(no);
    redefineAltura(filhoDir);

    return filhoDir;
}

int getBalance(No *no)
{
    return (no ? (alt(no->esq) - alt(no->dir)) : 0);
}

No *insereNo(No *raiz, Objeto *chave)
{
    if (!raiz)
        return criaNo(chave);

    /* pensar em como assinalar predecessor e sucessor agora */

    /*insere normalmente*/
    if (compara(chave, raiz->chave, 1))
        raiz->esq = insereNo(raiz->esq, chave);
    else
        raiz->dir = insereNo(raiz->dir, chave);

    /*atualiza a altura de um momento antes */
    redefineAltura(raiz);

    int a = getBalance(raiz);

    /* o problema na altura ocorreu na subarvore esquerda
     e o no foi inserido a esquerda do filho esquerdo, entao para balancear basta rodar para direita, 
     pq o filho esquerdo vai virar a nova raiz balanceando as alturas
     */
    if (a > 1 && chave < raiz->esq->chave)
        return rotacionaDir(raiz);

    /*problema na subarvore esquerda
    e o no foi inserido a direita do filho esquerdo, 
    entao eu transformo no caso anterior e rotaciono para direita de novo
     */
    if (a > 1 && chave > raiz->esq->chave)
    {
        raiz->esq = rotacionaEsq(raiz->esq);
        return rotacionaDir(raiz);
    }

    /* espelhado do caso para esquerda */
    if (a < -1 && chave > raiz->dir->chave)
        return rotacionaEsq(raiz);

    if (a < -1 && chave < raiz->dir->chave)
    {
        raiz->dir = rotacionaDir(raiz->dir);
        return rotacionaEsq(raiz);
    }

    return raiz;
}

No *menor(No *raiz)
{
    while (raiz->esq)
        raiz = raiz->esq;

    return raiz;
}

No *deleteNo(No *raiz, Objeto *chave)
{
    No *aux;
    /* deleta normalmente */
    if (raiz == NULL)
        return raiz;

    if (chave == raiz->chave)
    {
        aux = raiz;
        if (raiz->esq && raiz->dir)
        {
            raiz = menor(raiz->dir);
            raiz->esq = aux->esq;
            raiz->dir = aux->dir;
            raiz->dir = deleteNo(raiz->dir, raiz->chave);
        }
        else
        {
            raiz = (raiz->esq ? raiz->esq : raiz->dir);
        }
        free(aux);
    }
    else if (compara(chave, raiz->chave, 1))
    {
        raiz->esq = deleteNo(raiz->esq, chave);
    }
    else
    {
        raiz->dir = deleteNo(raiz->dir, chave);
    }

    if(raiz == NULL)
        return raiz;

    int a = getBalance(raiz);

    
    if (a > 1 && getBalance(raiz->esq) >= 0){
        return rotacionaDir(raiz);    
    }
    else if (a > 1)
    {
        raiz->esq = rotacionaEsq(raiz->esq);
        return rotacionaDir(raiz);
    }
    else if (a < -1 && getBalance(raiz->dir) <= 0){
        return rotacionaEsq(raiz);
    }
    else if(a < -1)
    {
        raiz->dir = rotacionaDir(raiz->dir);
        return rotacionaEsq(raiz);
    }

    return raiz;

}