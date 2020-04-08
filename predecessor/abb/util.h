#include<stdlib.h>
#ifndef _TIPO_H
#define _TIPO_H
#define max(a, b) ((a > b) ? a : b)

typedef struct Trajetoria
{
    double a;
    double b;
} Trajetoria;

enum{
    PONTO,
    CERTIFICADO
};

typedef struct No
{
    Objeto *chave;
    No *esq;
    No *dir;
    int alt;
} No;


typedef struct Objeto
{
    Trajetoria traj;
    double valor;
    struct Objeto * predecessor;
    struct Objeto * sucessor;
    No * no;
    /* ponteiro para o objeto correspondente (certificado-ponto menor)
     */
    struct Objeto * posicao;
    /* posicao em que o objeto se encontra no vetor do heap */
    int indice;
} Objeto;

typedef int Bool;

/* Funcao para comparar a e b de acordo com o parametro maior. Se maior = 1, retorna true caso a <= b.
    Se maior = 0, retorna true caso a >= b.
*/
Bool compara(Objeto * a, Objeto * b, Bool maior);

/* Troca o conteudo de a com o de b */
void swap(Objeto * a, Objeto * b);

#endif