#include"util.h"
#ifndef _MENU_H
#define _MENU_H

/* avanca no tempo */
void avancar(Objeto ** torneio, Objeto * heapCert, int n);

/*void criarPontos(Objeto * heapPontos, Objeto * heapCert, int n);*/

/*carrega os pontos de um arquivo que está no formato:
    nº de pontos
    coeficiente angular (espaço em branco) coeficiente linear (do primeiro ponto)
    coeficiente angular (espaço em branco) coeficiente linear (do segundo ponto)
    .....
    coeficiente angular (espaço em branco) coeficiente linear (do n-esimo ponto)
 */
void carregarArquivo(Objeto ** torneio, Objeto * heapCert, int n);

/*
    menu de opcoes
 */
int menu(Objeto ** torneio, Objeto * heapCert, int n);

/* consulta o valor maximo no tempo atual */
void query(Objeto ** torneio, Objeto * heapCert, int n);

void change(Objeto ** torneio, Objeto * heapCert, int n);

#endif