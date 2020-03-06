#include"heap.h"
#ifndef _CERTIFICADO_H
#define _CERTIFICADO_H

/* inicia */
void iniciaCertificados(Objeto * heapPontos, int indiceP, Objeto * heapCert, int n);

/* Calcula a validade do certificado entre dois pontos */
double calculaValidade(Objeto * pontoA, Objeto * pontoB);

/* Devolve quando será o próximo evento */
double proximoEvento(Objeto * heapCert);

/*
void atualizaIndCertificado(Objeto * indiceC, Objeto * indiceP);

void atualizaIndKDS(Objeto * indiceP, Objeto * indiceC);
*/

/* atualiza um certificado */
void atualizaCertificado(Objeto* heapPontos, Objeto * heapCert, Objeto * certificado, int n);

/* realiza todas as acoes inerentes a um evento:
    - conserta a KDS (torna ela verdadeira novamente);
    - atualiza os certificados necessarios;
 */
void evento(Objeto * heapPontos, Objeto * heapCert, int n);

#endif