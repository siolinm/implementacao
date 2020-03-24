#include"certificados.h"
#include"time.h"
#include"debug.h"
#include<stdio.h>

void iniciaCertificados(Objeto * arvore, Objeto * heapCert, int n){
    int i;
    
    // for(i = 1; i < n - 1; i++){        
    //     heapCert[i].valor = calculaValidade(arvore + i, arvore + 2*i);
    //     heapCert[i].posicao = arvore + i;
    //     heapCert[i].indice = i;
    //     db(printf("Certificado entre %d e %d expira em %g\n", i-1, i, heapCert[i].valor));
    // }
}

double calculaValidade(Objeto * pontoA, Objeto * pontoB){
    double t;
    if(pontoA->traj.a == pontoB->traj.a) return INFINITO;
    t = ((pontoB->traj.b - pontoA->traj.b)/(pontoA->traj.a - pontoB->traj.a));

    return (pontoA->traj.a - pontoB->traj.a) > 0 ? INFINITO : t;
}

double proximoEvento(Objeto * heapCert){
    db(printf("Proximo evento em %g\n", heapCert[1].valor));
    return heapCert[1].valor;
}

void atualizaCertificado(Objeto * heapCert, Objeto * certificado, int n){
    certificado->valor = calculaValidade((certificado->posicao), (certificado->posicao)->predecessor);    
    atualizaHeap(heapCert, n-1, certificado->indice, certificado->valor, 0);
}

void evento(Objeto * lista, Objeto * heapCert, int n){
    int index;
    double tempoAtual = getTime();
    
    // while(heapCert[1].valor == tempoAtual){
    //     index = (heapCert[1].posicao)->indice;
    //     swap(lista + index, lista + index - 1);
    //     if(index == 1){
    //         (lista[0].posicao)->posicao = lista + 1;
    //         lista[1].posicao = lista[0].posicao;
    //         lista[0].posicao = NULL;
    //         lista[0].indice = 0;
    //         lista[1].indice = 1;
    //     }
    //     else{
    //         (lista[index].posicao)->posicao = lista + index;
    //         (lista[index - 1].posicao)->posicao = lista + index - 1;
    //         lista[index].indice = index;
    //         lista[index - 1].indice = index - 1;
    //     }
    //     atualizaCertificado(lista, heapCert, lista[index].posicao, n);
    //     if(index > 1) atualizaCertificado(lista, heapCert, lista[index - 1].posicao, n);
    //     if(index < n-1) atualizaCertificado(lista, heapCert, lista[index + 1].posicao, n);        
    // }
}