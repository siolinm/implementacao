#include"util.h"
#include"cert.h"
#ifndef _TOURN_H
#define _TOURN_H

int tournMaxSize;

int tournElem;

/*
    Initializes the tourn
*/
void initTourn();

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



#endif