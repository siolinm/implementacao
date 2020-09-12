#include<stdlib.h>
#include<stdio.h>
#ifndef _UTIL_H
#define _UTIL_H
#define max(a, b) ((a > b) ? a : b)

/*
    cert[i] keeps the certificate between i/2 and i (the time that the certificate expires)
*/
double * cert;

/*
    speed[i] is the i-th element's speed
*/
double * speed;

/*
    x0[i] is the element's initial value
*/
double * x0;

/*
    tourn[1] is the maximum element
*/
int * tourn;

/*
    priority queue that keeps the certificates 
    the certificate with the earlier expiration time is in the first position
*/
int * Q;

/*
    indQ[i] it's the position of the i-th certificate in the priority queue Q;
*/
int * indQ;

/*
    indT[i] it's the position of the i-th element in tourn
*/
int * indT;

/*
    total number of elements
*/
int n;

/*
    maximum size supported by the vectors 
*/
int maxSize;

/*
    allocates the necessary memory for n elements
*/
void init(int m);

/* 
    deallocates the memory used 
*/
void destroy();


/*
    returns the value of the element in the i-th position in heap
*/
double value(int i);

/*
    swaps the i-th element in tourn with the j-th element
*/
void swapTourn(int i, int j);

typedef int Bool;

void printT();

void printC();

void printPQ();

void printIQ();

void printIT();

#endif