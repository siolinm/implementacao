#include"queries.h"
#include"avl.h"

No *criaNoQ(Object *key)
{
    No *novo = (No *)malloc(sizeof(No));

    novo->left = NULL;
    novo->right = NULL;
    novo->key = key;
    novo->height = 1;
    novo->children = 0;    

    return novo;
}

/* OK */
No *insereNoQ(No *raiz, Object *chave)
{
    int a;
    if (!raiz)
        return criaNoQ(chave);    

    /*insere normalmente*/
    if (chave->id < raiz->key->id)
        raiz->left = insereNoQ(raiz->left, chave);
    else
        raiz->right = insereNoQ(raiz->right, chave);
      
    /*atualiza a altura de um momento antes */
    redefineAltura(raiz);

    a = getBalance(raiz);

    /* o problema na altura ocorreu na subarvore esquerda
     e o no foi inserido a esquerda do filho esquerdo, entao para balancear basta rodar para direita, 
     pq o filho esquerdo vai virar a nova raiz balanceando as alturas
     */
    if (a > 1 && chave < raiz->left->key)
        return rotacionaDir(raiz);

    /*
    problema na subarvore esquerda
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
    int a;
    /* deleta normalmente */
    if (raiz == NULL)
        return raiz;

    if (chave->id == raiz->key->id)
    {                
        if (raiz->left && raiz->right)
        {
            aux = menor(raiz->right);
            raiz->key = aux->key;
            raiz->right = deleteNoQ(raiz->right, raiz->key);
        }
        else
        {
            aux = raiz;
            raiz = (raiz->left ? raiz->left : raiz->right);
            free(aux);
        }        
    }
    else if (chave->id < raiz->key->id)
    {
        raiz->left = deleteNoQ(raiz->left, chave);
    }
    else
    {
        raiz->right = deleteNoQ(raiz->right, chave);
    }

    if(raiz == NULL)
        return raiz;

    a = getBalance(raiz);
    
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
        return NULL;

    if(id < raiz->key->id)
        return queryQ(raiz->left, id);
    else if(id > raiz->key->id)
        return queryQ(raiz->right, id);
    
    return raiz->key;
}

void printQ(char * prefix, int size, No * r, int b){
	int i;
    char * novo;
    if(prefix == NULL){
        prefix = malloc(sizeof(*prefix));
        prefix[0] = '\0';
    }
    if(r != NULL)
    {
        for(i = 0; prefix[i] != '\0'; i++)
            printf("%c", prefix[i]);

        if(b) 
            printf("├──"); 
        else 
            printf("└──" );
        printf("%d: %g*t + %g = %g\n", r->key->id, r->key->speed, r->key->initv, value(r->key));        
		
        novo = malloc((size + 4)*sizeof(*novo));
        for(i = 0; i < size; i++)
            novo[i] = prefix[i];
        if(b)
            novo[size - 1] = '|';
        else
            novo[size - 1] = ' ';
        for(i = size; i < size + 4; i++)
            novo[i] = ' ';        
        novo[size + 3] = '\0';
		printQ(novo, size + 4, r->left, 1);
        printQ(novo, size + 4, r->right, 0);
        
    }
    if(!b)
        free(prefix);
}

void removeAllQ(No * raiz){
    if(!raiz)
        return;
    removeAllQ(raiz->left);
    removeAllQ(raiz->right);    
    free(raiz);
}