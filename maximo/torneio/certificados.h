#include"pq.h"
#include"time.h"
#include"debug.h"
#include"util.h"
#ifndef _CERTIFICADO_H
#define _CERTIFICADO_H

/*
    inicia cada certificado com seu devido valor
*/
void iniciaCertificados();

/*
    calcula a validade do certificado entre o elemento de indice a 
    e o elemento de indice b
*/
double calculaValidade(int a, int b);

/*
    atualiza o valor do certificado de indice i
*/
void atualizaCertificado(int i);

/*
    O primeiro certificado da fila de prioridade venceu;
*/
void evento();

#endif