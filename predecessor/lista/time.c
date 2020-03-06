#include"time.h"

static double tempoAtual = 0;

double getTime(){
    return tempoAtual;
}

void setTime(double t){
    tempoAtual = t;
}