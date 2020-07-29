#include "avl.h"
#include "certificados.h"
/*
    https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
    https://www.geeksforgeeks.org/avl-tree-set-2-deletion/
    https://www.youtube.com/watch?v=YkF76cOgtMQ&list=PLxI8Can9yAHf8k8LrUePyj0y3lLpigGcl&index=21
    https://www.youtube.com/watch?v=FzS0n_Z8lrk
*/


/* OK */
int altura(No *a)
{
    return (a ? a->height : -1);
}

/* OK */
void redefineAltura(No *a)
{
    a->height = max(altura(a->left), altura(a->right)) + 1;
}

/* OK */
No *criaNo(Object *key)
{
    No *novo = (No *)malloc(sizeof(No));

    novo->left = NULL;
    novo->right = NULL;
    novo->key = key;
    novo->height = 1;
    key->node = novo;

    return novo;
}

/* OK */
No *rotacionaDir(No *no)
{
    No *filhoEsq, *aux;

    filhoEsq = no->left;
    if (!filhoEsq)
        return no;
    aux = filhoEsq->right;

    filhoEsq->right = no;
    no->left = aux;

    redefineAltura(no);
    redefineAltura(filhoEsq);

    return filhoEsq;
}

/* OK */
No *rotacionaEsq(No *no)
{
    No *filhoDir, *aux;

    filhoDir = no->right;
    if (!filhoDir)
        return no;
    aux = filhoDir->left;

    filhoDir->left = no;
    no->right = aux;

    redefineAltura(no);
    redefineAltura(filhoDir);

    return filhoDir;
}

/* OK */
int getBalance(No *no)
{
    return (no ? (altura(no->left) - altura(no->right)) : 0);
}

/* OK */
No *insereNo(No *raiz, Object *chave)
{
    if (!raiz)
        return criaNo(chave);

    /* pensar em como assinalar predecessor e sucessor agora */

    /*insere normalmente*/
    if (valor(chave) < valor(raiz->key))
        raiz->left = insereNo(raiz->left, chave);
    else
        raiz->right = insereNo(raiz->right, chave);
    /*
    - O predecessor de um nó é o maior elemento da subárvore esquerda e o sucessor é o menor elemento da subárvore direita.
    - Caso a subárvore esquerda não exista o predecessor dele é o primeiro nó menor do que ele "no caminho para cima" 
    (subo para o pai dele e checo se essa é a subárvore direita do pai dele), 
    se eu chegar na raiz sem achar um nó assim, então ele não tem predecessor. */
    if(chave->prev == NULL && valor(chave) >= valor(raiz->key)){
        /* achei o predecessor de quem inseri */
        chave->prev = raiz->key;
        chave->next = raiz->key->next;
        if(chave->next)
            chave->next->prev = chave;
        raiz->key->next = chave;        
    }
    else if(chave->next == NULL && valor(chave) < valor(raiz->key)){        
        /*
        - Caso a subárvore direita não exista o sucessor dele é o primeiro nó maior do que ele "no caminho para cima" 
        (subo para o pai dele e checo se essa é a subárvore esquerda do pai dele), 
        se eu chegar na raiz sem achar um nó assim, então ele não tem sucessor.
        */
        chave->next = raiz->key;
        chave->prev = raiz->key->prev;
        if(chave->prev)
            chave->prev->next = chave;
        raiz->key->prev = chave;
    }    
    /*atualiza a altura de um momento antes */
    redefineAltura(raiz);

    int a = getBalance(raiz);

    /* o problema na altura ocorreu na subarvore esquerda
     e o no foi inserido a esquerda do filho esquerdo, entao para balancear basta rodar para direita, 
     pq o filho esquerdo vai virar a nova raiz balanceando as alturas
     */
    if (a > 1 && chave < raiz->left->key)
        return rotacionaDir(raiz);

    /*problema na subarvore esquerda
    e o no foi inserido a direita do filho esquerdo, 
    entao eu transformo no caso anterior e rotaciono para direita de novo
     */
    if (a > 1 && chave > raiz->left->key)
    {
        raiz->left = rotacionaEsq(raiz->left);
        return rotacionaDir(raiz);
    }

    /* espelhado do caso para esquerda */
    if (a < -1 && chave > raiz->right->key)
        return rotacionaEsq(raiz);

    if (a < -1 && chave < raiz->right->key)
    {
        raiz->right = rotacionaDir(raiz->right);
        return rotacionaEsq(raiz);
    }

    return raiz;
}

/* OK */
No *menor(No *raiz)
{
    while (raiz->left)
        raiz = raiz->left;

    return raiz;
}

/* OK */
No *deleteNo(No *raiz, Object *chave)
{
    No *aux;
    /* deleta normalmente */
    if (raiz == NULL)
        return raiz;

    if (chave == raiz->key)
    {
        if(chave->prev)
            chave->prev->next = chave->next;
        if(chave->next)
            chave->next->prev = chave->prev;
        aux = raiz;
        if (raiz->left && raiz->right)
        {
            raiz = menor(raiz->right);
            raiz->left = aux->left;
            raiz->right = aux->right;
            raiz->right = deleteNo(raiz->right, raiz->key);
        }
        else
        {
            raiz = (raiz->left ? raiz->left : raiz->right);
        }
        free(aux);
    }
    else if (valor(chave) < valor(raiz->key))
    {
        raiz->left = deleteNo(raiz->left, chave);
    }
    else
    {
        raiz->right = deleteNo(raiz->right, chave);
    }

    if(raiz == NULL)
        return raiz;

    int a = getBalance(raiz);
    
    if (a > 1 && getBalance(raiz->left) >= 0){
        return rotacionaDir(raiz);    
    }
    else if (a > 1)
    {
        raiz->left = rotacionaEsq(raiz->left);
        return rotacionaDir(raiz);
    }
    else if (a < -1 && getBalance(raiz->right) <= 0){
        return rotacionaEsq(raiz);
    }
    else if(a < -1)
    {
        raiz->right = rotacionaDir(raiz->right);
        return rotacionaEsq(raiz);
    }

    return raiz;

}