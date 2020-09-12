#include"tempo.h"
#include"util.h"
#include"queries.h"
#include"avl.h"
#include"pq.h"
#include"certificados.h"
#include"debug.h"
#include<stdio.h>
#include<bits/time.h>
#include<time.h>
#ifndef _MENU_H
#define _MENU_H

/*
    avanca no tempo 
*/
void advance();

/*
    carrega os elementos de um arquivo que está no formato:
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
    consulta quem e' o i-esimo elemento 
*/
void query();

/*
    altera a velocidade do i-esimo elemento para nova velocidade informada
*/
void change();

/*
    insere elemento com velocidade v e valor inicial xt
*/
void insert();

/*
    deleta elemento com id i
*/
void delete();

/*
    Informa qual o prazo de vencimento do proximo certificado a vencer
*/
double proximoEvento();


#endif