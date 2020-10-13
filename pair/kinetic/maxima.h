#include"util.h"
#include"heapsort.h"
#include"cands.h"
#include"hits.h"

#ifndef _MAXIMA_H
#define _MAXIMA_H

typedef Point Item;

CandsNode * maximaRoot;

void initMaxima(int dir);

void initializeCandsHits(int dir);

#endif