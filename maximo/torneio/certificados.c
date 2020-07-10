#include"certificados.h"
#include<stdio.h>

void iniciaCertificados(){
    int i;
    for(i = 1; i <= n; i++){
        if(indT[i] != 1)
            cert[i] = calculaValidade(torneio[indT[i]/2], torneio[indT[i]]);
        else
            cert[i] = INFINITO;
    }
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
    int j;
    j = indT[i]; /* posicao onde o elemento i perde no torneio */
    if(j == 1){
        cert[i] = INFINITO;
        altera_chavePQ(i, cert[i]);
        return;
    }
    if(i < 1 || i > n)
        return;
    cert[i] = calculaValidade(torneio[j/2], torneio[j]);
    /* atualiza a fila de prioridade */  
    altera_chavePQ(i, cert[i]);
}

/* 
    O primeiro certificado da fila de prioridade venceu;
*/
void evento(){
    int i, j, irmao;    
    while(cert[i = minPQ()] == getTime()){
        j = indT[i];
        irmao = 2*(j/2) + !(j % 2);
        /* se mudar no advance mudar aqui */
        while(j > 1 && valor(j) >= valor(irmao)){
            torneio[j/2] = torneio[j];
            irmao = 2*(j/2) + !(j % 2);
            indT[torneio[irmao]] = irmao;
            atualizaCertificado(torneio[irmao]);
            
            j = j/2;
            irmao = 2*(j/2) + !(j % 2);
        }
        
        indT[torneio[j]] = j;
        atualizaCertificado(torneio[j]);

    }
}