#include"certificados.h"
#include<stdio.h>

void iniciaCertificados(){
    int i;
    for(i = 0; i < n - 1; i++)
        cert[i] = calculaValidade(sorted[i], sorted[i + 1]);    
}

/* calcula a validade do certificado entre o elemento de indice a e o elemento de indice b */
double calculaValidade(int a, int b){
    /* 
        assumindo que a ja' esta' a frente de b, 
        b so' ultrapassaria a com uma velocidade maior
    */
    if(speed[a] >= speed[b])
        return INFINITO;
    
    return (x0[a] - x0[b])/(speed[b] - speed[a]);
}

/* atualiza o valor do certificado de indice i*/
void atualizaCertificado(int i){
    if(i < 0 || i >= n - 1)
        return;
    cert[i] = calculaValidade(sorted[i], sorted[i + 1]);
    /* atualiza a fila de prioridade */
    #warning Atualizar a fila de prioridade
    altera_chavePQ(i, getTime());
}

/* 
    O primeiro certificado da fila de prioridade venceu;
*/
void evento(){
    int i;
    while(cert[i = minPQ(Q)] == getTime()){
        swap(sorted[i], sorted[i + 1]);
        atualizaCertificado(cert[i]);
        atualizaCertificado(cert[i - 1]);
        atualizaCertificado(cert[i + 1]);
    }
}