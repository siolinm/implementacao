#include "util.h"
#include "event.h"
#ifndef _ORDEREDLIST_H
#define _ORDEREDLIST_H

AVLNode * listRoot[3];

/*
    initializes the trees 
*/
void listInit();

/*
    inserts point a into the list with direction dir 
*/
void listInsert(Point * a, int dir);

/* 
    deletes point a from the list with direction dir 
*/
void listDelete(Point * a, int dir);

/*
    swapNodes
*/
void listSwap(Point * p, Point * q, int dir);

void newCertList(Point *p, int dir);

void updateListCert(Point * p, int dir);

double expireList(Point *a, Point * b, int dir);

/*
    returns the height of node a, -1 if NULL;
*/
int height(AVLNode *a);

/*
    recalculates the node a height and sets its new value;
*/
void setHeight(AVLNode *a);

/*
    returns a new node with key key;
*/
AVLNode *newAVLNode(Object *key, int direction);

/*
    rotates the node to the right
*/
AVLNode *rotateRight(AVLNode *no);

/*
    rotates the node to the left
*/
AVLNode *rotateLeft(AVLNode *no);

/*
    returns the node's balance, which is height(node->left) - height(node->right)
    0 if NULL
*/
int getBalance(AVLNode *no);

/*
    recursively inserts node r with key key and adjusts the linked list, returning the new root
*/
AVLNode *insertAVLNode(AVLNode *r, Object *key, int direction);

/*
    returns the leftmost in element in the subtree with root r
*/
AVLNode *leftmost(AVLNode *r);

/*
    recusiverly deletes from the avl tree the node with key key, adjusting the linked list in the process, returning the new root
*/
AVLNode *deleteAVLNode(AVLNode *r, Object *key, int dir);

/*
    queries for the k-th element in the avl tree
*/
Object * query_kth(AVLNode *r, int i);

/*
    Prints the avl tree horizontally (for debug)
*/
void print(char * prefix, int size, AVLNode * r, int b);

/*
   deallocates all memory used
*/
void removeAll(AVLNode * r);

#endif