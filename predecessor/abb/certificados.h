#include"debug.h"
#include"util.h"
#include"tempo.h"
#include"pq.h"
#ifndef _CERTIFICADO_H
#define _CERTIFICADO_H

void iniciaCertificados(No * raiz);

void criaCertificado(Object * obj);

double expire(Object * a, Object * b);

void update(Object * obj);

void evento();

#endif