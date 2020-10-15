#include"pq.h"
#include"debug.h"
#include"util.h"
#ifndef _CERT_H
#define _CERT_H

void initCertTourn(int dir);

double expireTourn(TournObject * a, TournObject * b);

double expireList(Point *a, Point * b, int dir);

void newCertTourn(TournObject * obj);

void newCertList(Point *p, int dir);

void updateTournCert(TournObject * a);

void updateListCert(Point * p, int dir);

void tournEvent();

void listEvent();

void horizontalEvent(Point * p, Point * q, int dir);

void upEvent(Point * p, Point * q, int dir);

void downEvent(Point * p, Point * q, int dir);

void event();

#endif