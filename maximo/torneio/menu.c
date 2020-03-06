#include"menu.h"
#include"time.h"
#include"certificados.h"
#include"torneio.h"
#include"debug.h"
#include<stdio.h>

int menu(Objeto ** torneio, Objeto * heapCert, int n){
    char opt;
    printf("(a)vancar\n");
    printf("(c)arregar arquivo\n");
    printf("(m)udar trajetória\n");
    printf("(p)arar\n");
    printf("(q)uery\n");
    printf(">>> ");
    scanf(" %c", &opt);
    if(opt == 'p'){
        freeTorneio(torneio, n);
        free(heapCert);
        return (0);
    } 
    if(opt == 'q') query(torneio, heapCert, n);
    if(opt == 'm') change(torneio, heapCert, n);
    if(opt == 'a') avancar(torneio, heapCert, n);
    if(opt == 'c') carregarArquivo(torneio, heapCert, n);

    return 0;
}
void change(Objeto ** torneio, Objeto * heapCert, int n){
    int i;
    double v;
    printf("Digite o ponto e a velocidade a ser alterada: ");
    scanf("%d %lf", &i, &v);
    i = i + n - 1;
    torneio[i]->traj.b = (torneio[i]->traj.a - v)*getTime() + torneio[i]->traj.b;
    torneio[i]->traj.a = v;
    if(torneio[i]->posicao) atualizaCertificado(torneio, heapCert, torneio[i]->posicao, n);    
    printf("O ponto %d agora se desloca com velocidade %g\n", i - n + 1, v);
    menu(torneio, heapCert, n);
}

void avancar(Objeto ** torneio, Objeto * heapCert, int n){
    double t;
    printf("Digite o novo valor do tempo: ");
    scanf("%lf", &t);
    while(t > proximoEvento(heapCert)){
        setTime(proximoEvento(heapCert));
        evento(torneio, heapCert, n);
    }
    setTime(t);
    menu(torneio, heapCert, n);
}

void query(Objeto ** torneio, Objeto * heapCert, int n){
    printf("%g\n", torneio[1]->traj.a*getTime() + torneio[1]->traj.b);
    menu(torneio, heapCert, n);
}

void carregarArquivo(Objeto ** torneio, Objeto * heapCert, int n){
    FILE * arquivo;
    int i = 0;
    char nomeDoArquivo[80];
    printf("Digite o nome do arquivo: ");
    scanf("%s", nomeDoArquivo);

    arquivo = fopen(nomeDoArquivo, "r");
    fscanf(arquivo, "%d\n", &n);    
    torneio = criaTorneio(n);
    for(i = 2*n-1; i >= n; i--){        
        fscanf(arquivo, "%lf %lf",&(torneio[i]->traj.a), &(torneio[i]->traj.b));
        torneio[i]->valor = torneio[i]->traj.b;
    }
    fclose(arquivo);    
    heapCert = iniciaHeap(n);
    simulaRodada(torneio, heapCert, n-1, 2*n-1);
    db(for(i = 1; i < n; i++){
        printf("Certificado referente ao ponto %d vence em %g, indice do certificado: %d\n", (heapCert[i].posicao)->indice, heapCert[i].valor, i);
    });
    constroiHeap(heapCert, n-1, 0);
    menu(torneio, heapCert, n);
}