#include"util.h"
#ifndef _CANDS_H
#define _CANDS_H

typedef Point Item;

/*
    Inserts key in the splay tree
*/
void insertCands(CandsNode * root, Item * key, int direction);

void deleteCands(CandsNode * root, Item * key, int direction);

CandsNode * querySuccessorCands(CandsNode * root, Item * p, int order, int dir);

CandsNode * queryPredecessorCands(CandsNode * root, Item * p, int order, int dir);

CandsNode * extractCands(CandsNode * root, CandsNode *low, CandsNode * up, int dir);

void joinCands(CandsNode * root, CandsNode * joinRoot, int dir);

/*

*/
Point * queryCands(Item * q, int dir);

/*
    Splays node x
*/
void splayCands(CandsNode * x);

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
    Compares items (points) a and b, if b should be on the left subtree of a returns 1, otherwise returns 0
*/
int compareCands(Item * a, Item * b, int dir);

/*
    Deallocate all memory used in the splay tree
*/
void freeAllCands(CandsNode * r);

/*
    Prints the splay tree (for debug)
*/
/*void print(char * prefix, int size, CandsNode * r, int b);*/

#endif