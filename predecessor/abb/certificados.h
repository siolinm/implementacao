#include"heap.h"
#ifndef _CERTIFICADO_H
#define _CERTIFICADO_H

/* inicia */
void iniciaCertificados(Objeto * lista, int n);

/* Calcula a validade do certificado entre dois pontos */
double calculaValidade(Objeto * pontoA, Objeto * pontoB);

/* Devolve quando sera o próximo evento */
double proximoEvento();

/* atualiza um certificado */
void atualizaCertificado(Objeto * certificado);

void insereCertificado(Objeto * ponto);

/* realiza todas as acoes inerentes a um evento:
    - conserta a KDS (torna ela verdadeira novamente);
    - atualiza os certificados necessarios;
 */
void evento();

#endif