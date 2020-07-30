#include"queries.h"
#include"util.h"
#include"avl.h"

/* OK */
No *insereNoQ(No *raiz, Object *chave)
{
    if (!raiz)
        return criaNo(chave);    

    /*insere normalmente*/
    if (chave->id < raiz->key->id)
        raiz->left = insereNo(raiz->left, chave);
    else
        raiz->right = insereNo(raiz->right, chave);
      
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
No *deleteNoQ(No *raiz, Object *chave)
{
    No *aux;
    /* deleta normalmente */
    if (raiz == NULL)
        return raiz;

    if (chave->id == raiz->key->id)
    {        
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
    else if (chave->id < raiz->key->id)
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

Object * queryQ(No * raiz, int id){
    if(!raiz)
        return -1;

    if(id < raiz->key->id)
        return queryQ(raiz->left, id);
    else if(id > raiz->key->id)
        return queryQ(raiz->right, id);
    
    return raiz->key;
}