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
        heapCert[indiceP].indice = heapPontos + indiceP;
        heapPontos[indiceP].indice = heapCert + indiceP;
        heapCert[indiceP].index = indiceP;
    }
    if(indiceP == n && indiceP >= 1){
        heapCert[1].valor = heapCert[indiceP].valor;
        heapCert[1].index = indiceP;
        heapCert[1].indice = heapCert[indiceP].indice;
        db(printf("O ultimo certificado foi enviado para a primeira posicao do heap\n"));
        heapPontos[indiceP].indice = heapCert + 1;        
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
    db(printf("Mudando o indice do ponto no certificado, novo indice: %d", indiceP));
    (*indiceC).indice = indiceP;
}

void atualizaIndKDS(Objeto * indiceP, Objeto * indiceC){
    db(printf("Mudando o indice do certificado no ponto, novo indice: %d", indiceP));
    (*indiceP).indice = indiceC;
}*/

void atualizaCertificado(Objeto* heapPontos, Objeto * heapCert, Objeto * certificado, int n){
    certificado->valor = calculaValidade(heapPontos + ((*certificado->indice).index)/2, heapPontos + ((*certificado->indice).index));
    db(printf("Certificado entre ponto %d e %d atualizado com valor %g, tempo atual: %g\n", ((*certificado->indice).index)/2, (*certificado->indice).index, certificado->valor, getTime()));
    atualizaHeap(heapCert, n-1, certificado->index, certificado->valor, 0);
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
        indiceP = (*(heapCert[1].indice)).index;
        swap(heapPontos + indiceP, heapPontos + indiceP/2);    
        if(indiceP/4 >= 1){
            (*(heapPontos[indiceP].indice)).indice = heapPontos + indiceP;
            (*(heapPontos[indiceP/2].indice)).indice = heapPontos + indiceP/2;
            heapPontos[indiceP].index = indiceP;
            heapPontos[indiceP/2].index = indiceP/2;
        }
        else{
            (*(heapPontos[indiceP/2].indice)).indice = heapPontos + indiceP;
            heapPontos[indiceP].indice = heapPontos[indiceP/2].indice;
            heapPontos[indiceP/2].indice = NULL;
            heapPontos[indiceP].index = indiceP;
            heapPontos[indiceP/2].index = indiceP/2;
        }            
        atualizaCertificado(heapPontos, heapCert, heapPontos[indiceP].indice, n);
        if(indiceP/4 >= 1) atualizaCertificado(heapPontos, heapCert, heapPontos[indiceP/2].indice, n);
        if((2*(indiceP/2) + !(indiceP % 2)) <= n) atualizaCertificado(heapPontos, heapCert, heapPontos[2*(indiceP/2) + !(indiceP % 2)].indice, n);
        if(2*indiceP <= n) atualizaCertificado(heapPontos, heapCert, heapPontos[2*indiceP].indice, n);
        if(2*indiceP + 1 <= n) atualizaCertificado(heapPontos, heapCert, heapPontos[2*indiceP + 1].indice, n);
    }
}