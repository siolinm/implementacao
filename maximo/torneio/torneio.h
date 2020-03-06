#include"util.h"
#include"certificados.h"
#ifndef _TORNEIO_H
#define _TORNEIO_H

Objeto ** criaTorneio(int n);

void simulaRodada(Objeto ** torneio, Objeto * heapCert, int lastPos, int size);

void freeTorneio(Objeto ** torneio, int n);

#endif