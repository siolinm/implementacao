#include "avl.h"
/*
    https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
    https://www.geeksforgeeks.org/avl-tree-set-2-deletion/
    https://www.youtube.com/watch?v=FzS0n_Z8lrk
*/

No *raiz = NULL;

int altura(No *a)
{
    return (a ? a->alt : 0);
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

    no->alt = max(no->esq->alt, no->dir->alt) + 1;
    filhoEsq->alt = max(filhoEsq->esq->alt, filhoEsq->dir->alt) + 1;

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

    no->alt = max(no->esq->alt, no->dir->alt) + 1;
    filhoDir->alt = max(filhoDir->esq->alt, filhoDir->dir->alt) + 1;

    return filhoDir;
}

int getBalance(No *no)
{
    return (no ? (no->esq->alt - no->dir->alt) : 0);
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
    raiz->alt = max(raiz->dir->alt, raiz->esq->alt) + 1;

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