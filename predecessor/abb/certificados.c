#include"certificados.h"
#include"time.h"
#include"debug.h"
#include<stdio.h>

int nCertificados, maxSize;

void dobraTamanho(Objeto ** heapCert){
    int i;
    Objeto * novoArray = malloc((maxSize + 1)*sizeof(Objeto));
    maxSize = maxSize << 1;
    for(i = 1; i <= nCertificados; i++) novoArray[i] = (*heapCert)[i];
    free(heapCert);
    *heapCert = novoArray;
}

void insereCertificado(Objeto * ponto, Objeto * heapCert){
    if(nCertificados == maxSize) dobraTamanho(&heapCert);
    heapCert[++nCertificados].posicao = ponto;
    heapCert[nCertificados].indice = nCertificados;
    heapCert[nCertificados].valor = calculaValidade(ponto, ponto->predecessor);
    atualizaHeap(heapCert, nCertificados, nCertificados, heapCert[nCertificados].valor, 0);
}

void criaCertificados(Objeto * ponto, Objeto * heapCert, int n){
    int i = 1;
    while(ponto->predecessor != NULL){
        heapCert[i].indice = i;
        heapCert[i].posicao = ponto;
        heapCert[i].valor = calculaValidade(ponto, ponto->predecessor);
        i++;
    }
    nCertificados = i;
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

void atualizaCertificado(Objeto * heapCert, Objeto * certificado){
    certificado->valor = calculaValidade((certificado->posicao), (certificado->posicao)->predecessor);    
    atualizaHeap(heapCert, nCertificados, certificado->indice, certificado->valor, 0);
}

void evento(Objeto * raiz, Objeto * heapCert){
    int index;
    double tempoAtual = getTime();
    
    Objeto * antigosucessor, *novosucessor;

    while(heapCert[1].valor == tempoAtual){        
        antigosucessor = heapCert[1].posicao;
        novosucessor = antigosucessor->predecessor;
        antigosucessor->no = novosucessor->no;
        antigosucessor->no->chave = antigosucessor;
        novosucessor->no = antigosucessor->no;
        novosucessor->no->chave = novosucessor;
        
    }    
}