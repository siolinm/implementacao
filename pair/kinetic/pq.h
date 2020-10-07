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
void updatePQ(PQObject * c, double t);

/*
    assegurates the heap property by "sieving" elements
*/
void sieve(int i, int m);

/*
    inserts object obj in the PQ
*/
void insertPQ(PQObject * obj);

/*
    deletes object obj from the PQ
*/
void deletePQ(PQObject * obj);

#endif