#include"certificados.h"
#include"pq.h"
#include<stdio.h>

void iniciaCertificados(){
    int i;
    for(i = 2; i <= n; i++)
        cert[i] = calculaValidade(heap[i/2], heap[i]);    
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
    if(i <= 1 || i > n)
        return;
    cert[i] = calculaValidade(heap[i/2], heap[i]);
    /* atualiza a fila de prioridade */    
    altera_chavePQ(i, cert[i]);
}

/* 
    O primeiro certificado da fila de prioridade venceu;
*/
void evento(){
    int i;    
    while(cert[i = minPQ()] == getTime()){
        swapheap(i, i/2);               
        atualizaCertificado(i); /* ele e o pai */
        atualizaCertificado(i/2); /* pai com pai dele*/
        atualizaCertificado(2*(i/2) + !(i % 2)); /* irmao com pai */
        atualizaCertificado(2*i); /* filhos */
        atualizaCertificado(2*i + 1);
    }
}