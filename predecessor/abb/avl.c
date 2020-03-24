#include"avl.h"
/*
    https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
    https://www.geeksforgeeks.org/avl-tree-set-2-deletion/
    https://www.youtube.com/watch?v=FzS0n_Z8lrk
*/
int altura(No * a){
    return (a ? a->alt : 0);
}

No * criaNo(Objeto * chave){
    No * novo = (No *)malloc(sizeof(No));

    novo->esq = NULL;
    novo->dir = NULL;
    novo->chave = chave;
    novo->alt = 1;

    return novo;
}

No * rotacionaDir(No * no){
    No * filhoEsq, * aux;
    
    filhoEsq = no->esq;
    if(!filhoEsq) return no;
    aux = filhoEsq->dir;
    
    filhoEsq->dir = no;
    no->esq = aux;

    no->alt = max(no->esq->alt, no->dir->alt) + 1;
    filhoEsq->alt = max(filhoEsq->esq->alt, filhoEsq->dir->alt) + 1;

    return filhoEsq;
}

No * rotacionaEsq(No * no){
    No * filhoDir, * aux;
    
    filhoDir = no->dir;
    if(!filhoDir) return no;
    aux = filhoDir->esq;
    
    filhoDir->esq = no;
    no->dir = aux;

    no->alt = max(no->esq->alt, no->dir->alt) + 1;
    filhoDir->alt = max(filhoDir->esq->alt, filhoDir->dir->alt) + 1;
    
    return filhoDir;
}

int getBalance(No * no){
    return (no ? (no->esq->alt - no->dir->alt) : 0);
}

No * insereNo(No * raiz, Objeto * chave){
    if(!raiz) return criaNo(chave);
    
    
}