#include"util.h"
#ifndef _CANDS_H
#define _CANDS_H

typedef Point Item;

/*
    Root of the splay tree
*/
CandsNode * root;

/*
    Inserts key in the splay tree
*/
void insertCands(Item * key);

/*
    Splays node x
*/
void splay(CandsNode * x);

/*
    Rotates node x to the left, if x was the root the root is updated
*/
void rotateLeftCands(CandsNode * x);

/*
    Rotates node x to the right, if x was the root the root is updated
*/
void rotateRightCands(CandsNode * x);

/*
    Creates a new node with key key
*/
CandsNode * createCandsNode(Item * key);

/*
    Query for low in dominance of p, using start as the root
*/
CandsNode * queryLow(Item * p, CandsNode * start);

/*
    Query for up in dominance of p, using start as the root
*/
CandsNode * queryUp(Item * p, CandsNode * start);

/*
    Extracts Cands(p) from the splay tree
*/
CandsNode * cands(Item * p);

/*
    Looks for the point with minimum x in Cands(p) with root lcandsRoot
*/
Item * lcand(CandsNode * lcandsRoot, Item * min);

/*
    Compares items (points) a and b, if b should be on the left subtree of a returns 1, otherwise returns 0
*/
int compare(Item * a, Item * b);

/*
    Deallocate all memory used in the splay tree
*/
void freeAll(CandsNode * r);

/*
    Prints the splay tree (for debug)
*/
void print(char * prefix, int size, CandsNode * r, int b);

#endif