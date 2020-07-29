#include"certificados.h"
#include"util.h"
#include"tempo.h"
#include"pq.h"
#include<stdio.h>

void iniciaCertificados(No * raiz){
    if(!raiz)
        return; 
    iniciaCertificados(raiz->left);
    iniciaCertificados(raiz->right);
    criaCertificado(raiz->key);
}

void criaCertificado(Object * obj){
    obj->certificate = expire(obj, obj->next);
}

double expire(Object * a, Object * b){
    if(b == NULL || a->speed >= b->speed)
        return INFINITO;

    return (a->initv - b->initv)/(b->speed - a->speed);
}

void update(Object * obj){
    if(obj == NULL)
        return;
    updatePQ(obj, expire(obj, obj->next));
}

void evento(){
    Object * obj = minPQ();
    while(obj->certificate == getTime()){
        swapObjects(obj, obj->next);
        update(obj);
        update(obj->prev);
        update(obj->next);
        obj = minPQ();
    }
}