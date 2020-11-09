#include"util.h"
#include"tourn.h"
#include"cert.h"
#include"pq.h"
#include"hits.h"
#include"orderedlist.h"
#include"maxima.h"
#include"cands.h"
#ifndef _KDS_H
#define _KDS_H

/* 
    advance in time
*/
void advance(double t);

/* 
    queries for the element with maximum value
*/
void query();

/*
    changes the speed of the i-th element
*/
void change(int j, Vector v);

/*
    inserts element with speed v and current value xt
*/
void insert(Coordinate xt, Vector v);

/*
    deletes element with id i
*/
void delete(int i);

/*
    initialize a KDS with m elements 
*/
void initKDS();

/*
    build the kds
*/
void buildKDS();

/*
    Initializes data for a point
*/
void initializePoint(Point * p);

/*
    returns the next event time
*/
double nextEvent();

#endif