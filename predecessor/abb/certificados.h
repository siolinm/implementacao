#include"debug.h"
#include"util.h"
#include"tempo.h"
#include"pq.h"
#ifndef _CERTIFICADO_H
#define _CERTIFICADO_H

/*
    Inicia recursivamente os certificados entre os elementos da arvore, com raiz raiz
*/
void iniciaCertificados(No * raiz);

/*
    Calcula o certificado do objeto obj
*/
void criaCertificado(Object * obj);

/*
    Calcula quando expira o certificado entre a e b, se b e' null ou possui velocidade menor que a, retorna infinito
*/
double expire(Object * a, Object * b);

/*
    Atualiza o certificado do objeto obj
*/
void update(Object * obj);

/*
    Dispara um evento
*/
void evento();

#endif