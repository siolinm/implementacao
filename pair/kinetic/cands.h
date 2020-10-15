#include"util.h"
#ifndef _CANDS_H
#define _CANDS_H

void updateMinimumCands(CandsNode * a, int dir);

CandsNode * minimumCands(CandsNode * a, CandsNode * b, int dir);

CandsNode * createCandsNode(Item * key, int dir);

CandsNode * initCands(Item * p, int dir);

Point * queryCands(Item * q, int dir);

CandsNode * querySuccessorCands(CandsNode * root, Item * p, int order, int dir);

CandsNode * queryPredecessorCands(CandsNode * root, Item * p, int order, int dir);

CandsNode * extractCands(CandsNode * root, CandsNode *low, CandsNode * up, int dir);

void joinCands(CandsNode * root, CandsNode * joinRoot, int dir);

void rotateLeftCands(CandsNode * x, int dir);

void rotateRightCands(CandsNode * x, int dir);

void deleteCands(CandsNode * root, Item * key, int direction);

void swapCands(CandsNode *a, CandsNode * b, int dir);

CandsNode * successorCands(CandsNode * root);

CandsNode * deleteCandsR(CandsNode * root, Item * key, CandsNode **parent, int dir);

void insertCands(CandsNode * root, Item * key, int direction);

CandsNode * insertCandsR(CandsNode * root, CandsNode * no, int dir);

void splayCands(CandsNode * x, int dir);

int compareCands(Item * a, Item * b, int dir);

void freeAllCands(CandsNode * r);

#endif