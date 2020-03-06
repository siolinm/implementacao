#include"heap.h"
#include"time.h"
#include"debug.h"
#include<stdio.h>
#ifndef _CERTIFICADO_H
#define _CERTIFICADO_H

/* inicia */
void criaCertificado(Objeto ** torneio, Objeto * heapCert, Objeto * perdedor, Objeto * vencedor);

/* Calcula a validade do certificado entre dois pontos */
double calculaValidade(Objeto * pontoA, Objeto * pontoB);

/* Devolve quando será o próximo evento */
double proximoEvento(Objeto * heapCert);

/* atualiza um certificado */
void atualizaCertificado(Objeto ** torneio, Objeto * heapCert, Objeto * certificado, int n);

/* realiza todas as acoes inerentes a um evento:
    - conserta a KDS (torna ela verdadeira novamente);
    - atualiza os certificados necessarios;
 */
void evento(Objeto ** torneio, Objeto * heapCert, int n);

void atualizaTorneio(Objeto ** torneio, Objeto * heapCert, int pos, int n);

#endif