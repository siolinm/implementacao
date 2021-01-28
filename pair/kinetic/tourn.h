#include"util.h"
#include"event.h"
#ifndef _TOURN_H
#define _TOURN_H

int tournMaxSize;

int tournElem;

void initTourn(int cap);

void sendTourn(Point * p, int dir);

void updateTourn(Point * p, int dir);

void printTourn();

void printT(char * prefix, int size, int j, int b);

/*
    Builds the tourn
*/
void buildTourn();

/*
    inserts obj in tourn and updates all needed certificates
*/
void insertTourn(Point *p, int dir);

/*
    deletes obj of tourn
*/
void deleteTourn(Point *p, int dir);

int compareTourn(int i, int j);

void resizeTourn();

void initCertTourn();

double expireTourn(TournObject * a, TournObject * b);

void newCertTourn(TournObject * obj);

void updateTournCert(TournObject * a);

#endif