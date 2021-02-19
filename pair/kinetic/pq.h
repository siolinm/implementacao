#include<stdio.h>
#include<stdlib.h>
#include"util.h"
#include"debug.h"
#ifndef _PQ_H
#define _PQ_H

int pqSize;

int pqMaxSize;

/*
    initializes the priority queue
*/
void initPQ();

/*
    returns the certificate with minimum value
*/
PQObject * minPQ();

/*
    returns the value of the certificate in the i-th priority queue position
*/
double valuePQ(int i);

/*
    returns the value of the certificate in the i-th priority queue position
*/
double valuePQObject(PQObject * obj);

/*
    updates the PQObject c certificate to value t and adjusts Q
*/
void updatePQ(Point * p, int certType, double t);

/*
    assegurates the heap property by "sieving" elements
*/
void sink(int i, int m);

void swim(int i);

/*
    inserts point p with cert certType in the PQ
*/
void insertPQ(Point * p, int certType);

/*
    deletes object obj from the PQ
*/
void deletePQ(Point * p, int certType);

/*

*/
void printPQ();

#endif