#include"certificados.h"
#include<stdio.h>

void iniciaCertificados(No * raiz){
    if(!raiz)
        return; 
    iniciaCertificados(raiz->left);
    iniciaCertificados(raiz->right);
    criaCertificado(raiz->key);
}

void criaCertificado(Object * obj){
    obj->certificate = expire(obj, obj->prev);
}

double expire(Object * a, Object * b){
    if(b == NULL || a->speed >= b->speed)
        return INFINITO;

    return (a->initv - b->initv)/(b->speed - a->speed);
}

void update(Object * obj){
    if(obj == NULL)
        return;
    updatePQ(obj, expire(obj, obj->prev));
}

void evento(){
    Object * obj = minPQ();
    while(obj->certificate == getTime()){
        swapObjects(obj, obj->prev);
        printL();
        obj = obj->next;
        update(obj);
        update(obj->prev);
        update(obj->next);
        obj = minPQ();
    }
}