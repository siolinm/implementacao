#include"menu.h"
#include"time.h"
#include"util.h"
#include"certificados.h"
#include"debug.h"
#include<stdio.h>

int menu(Objeto * heapPontos, Objeto * heapCert, int n){
    char opt;
    printf("(a)vancar\n");
    printf("(c)arregar arquivo\n");
    printf("(p)arar\n");
    printf("(q)uery\n");
    printf(">>> ");
    scanf(" %c", &opt);
    if(opt == 'p')
    {
        free(heapPontos);
        free(heapCert);
        return (0);        
    } 
    if(opt == 'q') query(heapPontos, heapCert, n);
    if(opt == 'a') avancar(heapPontos, heapCert, n);
    if(opt == 'c') carregarArquivo(heapPontos, heapCert, n);

    return 0;
}

void avancar(Objeto * heapPontos, Objeto * heapCert, int n){
    double t;
    printf("Digite o novo valor do tempo: ");
    scanf("%lf", &t);
    while(t > proximoEvento(heapCert)){
        setTime(proximoEvento(heapCert));
        evento(heapPontos, heapCert, n);
    }
    setTime(t);
    menu(heapPontos, heapCert, n);
}

void query(Objeto * heapPontos, Objeto * heapCert, int n){
    printf("%g\n", heapPontos[1].traj.a*getTime() + heapPontos[1].traj.b);
    menu(heapPontos, heapCert, n);
}

void carregarArquivo(Objeto * heapPontos, Objeto * heapCert, int n){
    FILE * arquivo;
    int i = 0;
    char nomeDoArquivo[80];
    printf("Digite o nome do arquivo: ");
    scanf("%s", nomeDoArquivo);

    arquivo = fopen(nomeDoArquivo, "r");
    fscanf(arquivo, "%d\n", &n);
    heapPontos = iniciaHeap(n);                
    for(i = 1; i <= n; i++) fscanf(arquivo, "%lf %lf",&(heapPontos[i].traj.a), &(heapPontos[i].traj.b));
    fclose(arquivo);
    constroiHeap(heapPontos, n, 1);
    heapCert = iniciaHeap(n);
    iniciaCertificados(heapPontos, 1, heapCert, n);
    db(for(i = 1; i < n; i++){
        printf("Certificado referente ao ponto %d vence em %g,  do certificado: %d\n", heapCert[i].posicao->indice, heapCert[i].valor, i);
    });
    constroiHeap(heapCert, n-1, 0);
    menu(heapPontos, heapCert, n);
}