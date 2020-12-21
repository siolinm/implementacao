#include"util.h"
#include<stdio.h>
#ifndef _SPLAY_H
#define _SPLAY_H

void insertS(void * root, Point * a, int type, int dir);

void deleteS(void * root, Point * a, int type, int dir);

void splay(void * x, int type, int dir);

void * splitL(void *root, int type, int dir);

void * splitR(void * root, int type, int dir);

void * joinS(void * rootS, void * rootL, int type, int dir);

void * successorS(void * root, Item * p, int type, int dir, int order);

void * predecessorS(void * root, Item * p, int type, int dir, int order);

Point * ownerS(void * root, int type, int dir);

void * extractS(void * root, void * low, void * up, int type, int dir);

/* ---------------------------------------------- */

void rotateLeftS(void * x, int type, int dir);

void rotateRightS(void * x, int type, int dir);

void initS(Point * p, int type, int dir);

void * createNodeS(Point * key, int type, int dir);

void * insertSR(void * root, void * node, int type, int dir);

void * deleteSR(void * root, Point * a, void **parent, int type, int dir);

int compareS(Point * a, Point * b, int type, int dir);

void swapS(void * roota, void * rootb, int type, int dir);

void freeAllS(void * root, int type);

/* ---------------------------------------------- */

void attach(void * roota, void * rootb, int type, int dir);

void * detach(void * root, int type, int dir);

void setLeftS(void * x, void * y, int type);

void setRightS(void * x, void * y, int type);

void setParentS(void * x, void * y, int type);

void setLeftmostS(void * x, void * y, int type);

void setKeyS(void * x, Point * a, int type);

void * getLeftS(void * x, int type);

void * getRightS(void * x, int type);

void * getParentS(void * x, int type);

void * getLeftmostS(void * x, int type);

Point * getKeyS(void * x, int type);

void updateLeftmost(void * x, int dir);

void printS(void * root, int type);

void printSR(void * root, char * prefix, int type, int size, int b);

#endif