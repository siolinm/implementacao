#include"pq.h"
#include"debug.h"
#include"util.h"
#ifndef _CERT_H
#define _CERT_H

void tournEvent();

void listEvent();

void horizontalEvent(Point * p, Point * q, int dir);

void upEvent(Point * p, Point * q, int dir);

void downEvent(Point * p, Point * q, int dir);

void event();

#endif