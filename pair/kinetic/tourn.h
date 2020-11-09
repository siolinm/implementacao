#include"util.h"
#include"cert.h"
#ifndef _TOURN_H
#define _TOURN_H

int tournMaxSize;

int tournElem;

/*
    Builds the tourn
*/
void buildTourn();

/*
    inserts obj in tourn and updates all needed certificates
*/
void insertTourn(TournObject * obj, int dir);

/*
    deletes obj of tourn
*/
void deleteTourn(TournObject * obj);

int compareTourn(int i, int j);

void resizeTourn();

void initCertTourn(int dir);

double expireTourn(TournObject * a, TournObject * b);

void newCertTourn(TournObject * obj);

void updateTournCert(TournObject * a);

#endif