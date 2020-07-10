#include<stdio.h>
#include"util.h"
#include"torneio.h"
#include"certificados.h"
#include"pq.h"
#ifndef _MENU_H
#define _MENU_H

/* 
    avanca no tempo 
*/
void advance();

/*carrega os elementos de um arquivo que está no formato:
    nº de elementos
    coeficiente angular (espaço em branco) coeficiente linear (do primeiro elemento)
    coeficiente angular (espaço em branco) coeficiente linear (do segundo elemento)
    .....
    coeficiente angular (espaço em branco) coeficiente linear (do n-esimo elemento)
 */
void carregarArquivo();

/*
    menu de opcoes
 */
int menu();

/* 
    consulta quem e' o predecessor do i-esimo elemento 
*/
void query();

/*
    altera a velocidade do i-esimo elementos para nova velocidade informada
*/
void change();

/*
    Informa qual o prazo de vencimento do proximo certificado a vencer
*/
double proximoEvento();

#endif