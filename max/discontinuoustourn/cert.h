#include"pq.h"
#include"currentTime.h"
#include"debug.h"
#include"util.h"
#ifndef _CERT_H
#define _CERT_H

/*
    Initializes all certificates
*/
void initCert();

/*
    Calculates the certtificate for the new object obj
*/
void newCert(Object * obj);

/*
    Calculates the expiration time between elements a and b
*/
double expire(Object * a, Object * b);

/*
    updates the obj certificate
*/
void update(Object *obj);

/*
    An event
*/
void event();

#endif