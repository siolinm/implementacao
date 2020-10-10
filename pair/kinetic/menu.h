#include<stdio.h>
#include"util.h"
#include"tourn.h"
#include"cert.h"
#include"pq.h"
#include"cands.h"
#ifndef _MENU_H
#define _MENU_H

/* 
    advance in time
*/
void advance(double t);

/*
loads the elements from a file in the following format:
    number of elements
    x0 y0 (whitespace) vx vy (of the first element)
    x0 y0 (whitespace) vx vy (of the second element)
    .....
    x0 y0 (whitespace) vx vy (of the n-th element)
 */
void loadFile();

/*
    options menu
 */
int menu();

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
    returns the next event time
*/
double nextEvent();

#endif