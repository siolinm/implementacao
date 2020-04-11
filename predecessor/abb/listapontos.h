#include "util.h"

Objeto ** listaPontos;
int maxSize = 0;
int nPontos = 0;

Objeto ** listaPontos;

void inserePonto(Objeto * ponto);

Objeto * getPonto(int i);

void resize(int newSize);

void predecessor(int i);