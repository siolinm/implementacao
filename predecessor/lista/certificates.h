#include"pq.h"
#include"tempo.h"
#include"debug.h"
#include"util.h"
#ifndef _CERT_H
#define _CERT_H

/*
    Initializes the values of all certificates
*/
void initCert();

/*
    Calculates the value of the certificate between elements a and b
*/
double expire(int a, int b);

/*
    Recalculates the value of cert[i] and calls updatePQ
*/
void update(int i);

/*
    An event
*/
void event();

#endif