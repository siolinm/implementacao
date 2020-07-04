#ifndef _HEAPSORT_H
#define _HEAPSORT_H
#include"util.h"
#include"time.h"
#include"certificados.h"
#include<stdio.h>

/*
    Garante a propriedade do heap "descendo"/"peneirando"
    os elementos
*/
void peneiraHeap(int i, int m);

/*
    Constroi o heap e ordena o vetor sorted
*/
void heapsort();


#endif