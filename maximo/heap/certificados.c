#include"certificados.h"
#include"time.h"
#include"debug.h"
#include<stdio.h>

void iniciaCertificados(Objeto * heapPontos, int indiceP, Objeto * heapCert, int n){    
    if(indiceP > n) return;
    db(printf("Iniciando certificados em %d\n", 2*indiceP));
    iniciaCertificados(heapPontos, 2*indiceP, heapCert, n);
    db(printf("Iniciando certificados em %d\n", 2*indiceP + 1));
    iniciaCertificados(heapPontos, 2*indiceP+1, heapCert, n);
    
    if(indiceP/2 >= 1){
        heapCert[indiceP].valor = calculaValidade(heapPontos + indiceP/2, heapPontos + indiceP);
        db(printf("Certificado entre %d e %d expira em %g\n", indiceP/2, indiceP, heapCert[indiceP].valor));
        heapCert[indiceP].posicao = heapPontos + indiceP;
        heapPontos[indiceP].posicao = heapCert + indiceP;
        heapCert[indiceP].indice = indiceP;
    }
    if(indiceP == n && indiceP >= 1){
        heapCert[1].valor = heapCert[indiceP].valor;
        heapCert[1].indice = indiceP;
        heapCert[1].posicao = heapCert[indiceP].posicao;
        db(printf("O ultimo certificado foi enviado para a primeira posicao do heap\n"));
        heapPontos[indiceP].posicao = heapCert + 1;        
    }
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
/*
void atualizaIndCertificado(Objeto * indiceC, Objeto * indiceP){
    db(printf("Mudando o posicao do ponto no certificado, novo posicao: %d", indiceP));
    (*indiceC).posicao = indiceP;
}

void atualizaIndKDS(Objeto * indiceP, Objeto * indiceC){
    db(printf("Mudando o posicao do certificado no ponto, novo posicao: %d", indiceP));
    (*indiceP).posicao = indiceC;
}*/

void atualizaCertificado(Objeto* heapPontos, Objeto * heapCert, Objeto * certificado, int n){
    certificado->valor = calculaValidade(heapPontos + ((*certificado->posicao).indice)/2, heapPontos + ((*certificado->posicao).indice));
    db(printf("Certificado entre ponto %d e %d atualizado com valor %g, tempo atual: %g\n", ((*certificado->posicao).indice)/2, (*certificado->posicao).indice, certificado->valor, getTime()));
    atualizaHeap(heapCert, n-1, certificado->indice, certificado->valor, 0);
}

/*
    O certificado na posição 1 do heapCert venceu, ações:
        - Atualizar heapPontos, para torná-lo verdadeiro novamente;
        - Ajustar os 5 certificados: 
            - indiceP/2, indiceP, 2*(indiceP/2) + !(indiceP % 2), 2*indiceP, 2*indiceP+1;
            - Usar a função atualizaHeap;

        - Checar se o novo certificado na posição não venceu, se venceu repetir o processo.  
*/
void evento(Objeto * heapPontos, Objeto * heapCert, int n){
    int indiceP;
    double tempoAtual = getTime();
    
    while(heapCert[1].valor == tempoAtual){
        indiceP = (*(heapCert[1].posicao)).indice;
        swap(heapPontos + indiceP, heapPontos + indiceP/2);    
        if(indiceP/4 >= 1){
            (*(heapPontos[indiceP].posicao)).posicao = heapPontos + indiceP;
            (*(heapPontos[indiceP/2].posicao)).posicao = heapPontos + indiceP/2;
            heapPontos[indiceP].indice = indiceP;
            heapPontos[indiceP/2].indice = indiceP/2;
        }
        else{
            (*(heapPontos[indiceP/2].posicao)).posicao = heapPontos + indiceP;
            heapPontos[indiceP].posicao = heapPontos[indiceP/2].posicao;
            heapPontos[indiceP/2].posicao = NULL;
            heapPontos[indiceP].indice = indiceP;
            heapPontos[indiceP/2].indice = indiceP/2;
        }            
        atualizaCertificado(heapPontos, heapCert, heapPontos[indiceP].posicao, n);
        if(indiceP/4 >= 1) atualizaCertificado(heapPontos, heapCert, heapPontos[indiceP/2].posicao, n);
        if((2*(indiceP/2) + !(indiceP % 2)) <= n) atualizaCertificado(heapPontos, heapCert, heapPontos[2*(indiceP/2) + !(indiceP % 2)].posicao, n);
        if(2*indiceP <= n) atualizaCertificado(heapPontos, heapCert, heapPontos[2*indiceP].posicao, n);
        if(2*indiceP + 1 <= n) atualizaCertificado(heapPontos, heapCert, heapPontos[2*indiceP + 1].posicao, n);
    }
}