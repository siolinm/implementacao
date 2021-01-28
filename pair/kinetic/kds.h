#include"util.h"
#include"tourn.h"
#include"event.h"
#include"pq.h"
#include"orderedlist.h"
#include"maxima.h"
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
    free the kds
*/
void freeKDS();

/*
    Initializes data for a point
*/
void sendPoint(Point * p);

/*
    returns the next event time
*/
double nextEvent();

#endif