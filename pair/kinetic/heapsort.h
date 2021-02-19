#include"util.h"

#ifndef _HEAPSORT_H
#define _HEAPSORT_H

double valueHeapsort(Point **v, int i, int dir);

int compare(Point **v, int i, int j, int dir);

void swapHeapsort(int i, int j, Point ** v);

void sieveHeap(Point **v, int i, int m, int dir);

void heapsort(Point ** v, int dir);

#endif