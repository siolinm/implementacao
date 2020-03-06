#include"util.h"

Bool compara(Objeto * a, Objeto * b, Bool maior){
    return (maior ? (a->valor <= b->valor) : (a->valor >= b->valor));
}

void swap(Objeto * a, Objeto * b){
    Objeto c = *a;
    *a = *b;
    *b = c;
}