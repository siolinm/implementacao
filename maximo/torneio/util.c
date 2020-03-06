#include"util.h"

Bool compara(Objeto * a, Objeto * b, Bool maior){
    return (maior ? (a->valor <= b->valor) : (a->valor >= b->valor));
}

void setValor(Objeto * a, double time){
    a->valor = (a->traj).a*time + (a->traj).b;
}

void swap(Objeto * a, Objeto * b){
    Objeto c = *a;
    *a = *b;
    *b = c;
}

void mostrePonto(Objeto * ponto){
    printf("Trajetoria do ponto: %g * t + %g\n", ponto->traj.a, ponto->traj.b);    
}