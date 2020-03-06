#include"certificados.h"

int pos = 1;

void criaCertificado(Objeto ** torneio, Objeto * heapCert, Objeto * perdedor, Objeto * vencedor){    
    heapCert[pos].valor = calculaValidade(vencedor, perdedor);
    heapCert[pos].posicao = perdedor;
    heapCert[pos].indice = pos;
    perdedor->posicao = heapCert + pos;
    pos++;
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

void atualizaCertificado(Objeto ** torneio, Objeto * heapCert, Objeto * certificado, int n){
    certificado->valor = calculaValidade(torneio[certificado->posicao->indice/2], certificado->posicao);
    db(printf("Certificado entre ponto %d e %d atualizado com valor %g, tempo atual: %g\n", certificado->posicao->indice/2, certificado->posicao->indice, certificado->valor, getTime()));
    db(mostrePonto(torneio[certificado->posicao->indice/2]));
    db(mostrePonto(certificado->posicao));
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
void evento(Objeto ** torneio, Objeto * heapCert, int n){    
    double tempoAtual = getTime();
    
    while(heapCert[1].valor == tempoAtual){
        atualizaTorneio(torneio, heapCert, (heapCert[1].posicao)->indice, n);
    }
}


void atualizaTorneio(Objeto ** torneio, Objeto * heapCert, int pos, int n){
    int v = pos, p = 0;
    double time = getTime();
    while(v/2 >= 1 && torneio[v/2] != torneio[v]){        
        torneio[v - 2*(v%2) + 1]->indice = v - 2*(v%2) + 1;
        torneio[v]->indice = v/2; 
        if(v/2 == 1){
            torneio[v/2]->posicao = torneio[v]->posicao;
            torneio[v/2]->posicao->posicao = torneio[v/2];
            torneio[v/2]->indice = v - 2*(v%2) + 1;
            torneio[v]->posicao = NULL;
        }              
        torneio[v/2] = torneio[v];
        atualizaCertificado(torneio, heapCert, torneio[v - 2*(v%2) + 1]->posicao, n);
        if(v/2 == 1) break;
        v = v/2;
        v = v - v%2;
        setValor(torneio[v], time);
        setValor(torneio[v+1], time);
        /* se o v perdeu entao o vencedor deveria ser v+1*/
        if(!compara(torneio[v], torneio[v+1], 0)){
            p = v;
            v++;
        }
        else{
            p = v + 1;
        } 
    }
    if(p != 0){
        atualizaCertificado(torneio, heapCert, torneio[p]->posicao, n);
    }
}