#include"util.h"
#ifndef _HITS_H
#define _HITS_H

HitsNode * createHitsNode(Item * key, int dir, int up);

HitsNode * initHits(Item * p, int dir);

HitsNode * querySuccessorHits(HitsNode * root, Item * p, int dir);

HitsNode * queryPredecessorHits(HitsNode * root, Item * p, int dir);

Item * queryHitsLow(Item * q, int dir);

Item * queryHitsUp(Item * q, int dir);

void rotateLeftHits(HitsNode * x);

void rotateRightHits(HitsNode * x);

HitsNode * successorHits(HitsNode * root);

void swapHits(HitsNode *a, HitsNode * b, int dir);

void deleteHits(HitsNode * root, Item * key, int dir, int up);

HitsNode * deleteHitsR(HitsNode * root, Item * key, HitsNode **parent, int dir, int up);

void insertHits(HitsNode * root, Item * key, int dir, int up);

HitsNode * insertHitsR(HitsNode * root, HitsNode * no, int dir);

void splayHits(HitsNode * x);

int compareHits(Item * a, Item * b, int dir);

void freeAllHits(HitsNode * r);

#endif