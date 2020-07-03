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

// void iniciaCertificados(Objeto * lista, Objeto * heapCert, int n){        
//     int i;
    
//     for(i = 1; i < n; i++){
//         lista[i].indice = i;
//         lista[i].posicao = heapCert + i;
//         heapCert[i].valor = calculaValidade(lista + i, lista + i - 1);
//         heapCert[i].posicao = lista + i; 
//         heapCert[i].indice = i;
//         db(printf("Certificado entre %d e %d expira em %g\n", i-1, i, heapCert[i].valor));
//     }        
// }

// double calculaValidade(Objeto * pontoA, Objeto * pontoB){
//     double t;
//     if(pontoA->traj.a == pontoB->traj.a) return INFINITO;    
//     t = ((pontoB->traj.b - pontoA->traj.b)/(pontoA->traj.a - pontoB->traj.a));

//     return (pontoA->traj.a - pontoB->traj.a) > 0 ? INFINITO : t;
// }

// double proximoEvento(Objeto * heapCert){
//     db(printf("Proximo evento em %g\n", heapCert[1].valor));
//     return heapCert[1].valor;
// }

// void atualizaCertificado(Objeto* lista, Objeto * heapCert, Objeto * certificado, int n){
//     certificado->valor = calculaValidade( lista + (certificado->posicao)->indice, lista + (certificado->posicao)->indice - 1);
//     db(printf("Certificado entre ponto %d e %d atualizado com valor %g, tempo atual: %g\n", (certificado->posicao)->indice - 1, (certificado->posicao)->indice, certificado->valor, getTime()));
//     atualizaHeap(heapCert, n-1, certificado->indice, certificado->valor, 0);
// }

// /*
//     O certificado na posição 1 do heapCert venceu, ações:
//         - Atualizar heapPontos, para torná-lo verdadeiro novamente;
//         - Ajustar os 5 certificados: 
//             - indiceP/2, indiceP, 2*(indiceP/2) + !(indiceP % 2), 2*indiceP, 2*indiceP+1;
//             - Usar a função atualizaHeap;

//         - Checar se o novo certificado na posição não venceu, se venceu repetir o processo.  
// */
// void evento(Objeto * lista, Objeto * heapCert, int n){
//     int index;
//     double tempoAtual = getTime();
    
//     while(heapCert[1].valor == tempoAtual){
//         index = (heapCert[1].posicao)->indice;
//         swap(lista + index, lista + index - 1);
//         if(index == 1){
//             (lista[0].posicao)->posicao = lista + 1;
//             lista[1].posicao = lista[0].posicao;
//             lista[0].posicao = NULL;
//             lista[0].indice = 0;
//             lista[1].indice = 1;
//         }
//         else{
//             (lista[index].posicao)->posicao = lista + index;
//             (lista[index - 1].posicao)->posicao = lista + index - 1;
//             lista[index].indice = index;
//             lista[index - 1].indice = index - 1;
//         }
//         atualizaCertificado(lista, heapCert, lista[index].posicao, n);
//         if(index > 1) atualizaCertificado(lista, heapCert, lista[index - 1].posicao, n);
//         if(index < n-1) atualizaCertificado(lista, heapCert, lista[index + 1].posicao, n);        
//     }
// }