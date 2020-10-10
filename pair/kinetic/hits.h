#include"util.h"
#ifndef _HITS_H
#define _HITS_H

typedef Point Item;

/*
    Inserts key in the splay tree
*/
void insertHits(Item * key);

/*
    Splays node x
*/
void splayHits(HitsNode * x);

/*
    Rotates node x to the left
*/
void rotateLeftHits(HitsNode * x);

/*
    Rotates node x to the right
*/
void rotateRightHits(HitsNode * x);

/*
    Creates a new node with key key
*/
HitsNode * createHitsNode(Item * key);

/*
    Compares items (points) a and b, if b should be on the left subtree of a returns 1, otherwise returns 0
*/
int compareHits(Item * a, Item * b, int dir);

/*
    Deallocate all memory used in the splay tree
*/
void freeAllHits(HitsNode * r);

/*
    Prints the splay tree (for debug)
*/
/*void print(char * prefix, int size, HitsNode * r, int b);*/

#endif