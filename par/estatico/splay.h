#include"util.h"
#ifndef _SPLAY_H
#define _SPLAY_H

typedef Point Item;

typedef struct Node
{
    struct Node * left;
    struct Node * right;
    struct Node * parent;
    Item * key;
} Node;

Node * root;

void query(Item * key);

void insert(Item * key);

void remove(Item * key);

void splay(Node * x);

void rotateLeft(Node * x);

void rotateRight(Node * x);

Node * insertR(Node * root, Item * key);

Node * removeR(Node * root, Item * key);

Node * createNode(Item * key);

#endif