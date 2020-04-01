#include"heap.h"
#ifndef _CERTIFICADO_H
#define _CERTIFICADO_H

/* inicia */
void iniciaCertificados(Objeto * lista, Objeto * heapCert, int n);

/* Calcula a validade do certificado entre dois pontos */
double calculaValidade(Objeto * pontoA, Objeto * pontoB);

/* Devolve quando sera o próximo evento */
double proximoEvento(Objeto * heapCert);

/* atualiza um certificado */
void atualizaCertificado(Objeto * heapCert, Objeto * certificado);

/* realiza todas as acoes inerentes a um evento:
    - conserta a KDS (torna ela verdadeira novamente);
    - atualiza os certificados necessarios;
 */
void evento(Objeto * lista, Objeto * heapCert);

#endif