#include"menu.h"
#include"time.h"
#include"util.h"
#include"certificados.h"
#include"debug.h"
#include<stdio.h>

int menu(Objeto * abb, Objeto * heapCert, int n){
    char opt;
    printf("(a)vancar\n");
    printf("(c)arregar arquivo\n");
    printf("(m)udar trajetoria\n");
    printf("(p)arar\n");
    printf("(q)uery\n");
    printf(">>> ");
    scanf(" %c", &opt);
    if(opt == 'p'){
        if(heapCert) free(heapCert);
        return (0);
    } 
    if(opt == 'q') query(abb, heapCert, n);
    if(opt == 'a') avancar(abb, heapCert, n);
    if(opt == 'm') change(abb, heapCert, n);
    if(opt == 'c') carregarArquivo(abb, heapCert, n);

    return 0;
}

void avancar(Objeto * abb, Objeto * heapCert, int n){
    double t;
    printf("Digite o novo valor do tempo: ");
    scanf("%lf", &t);
    while(t > proximoEvento(heapCert)){
        setTime(proximoEvento(heapCert));
        evento(abb, heapCert, n);
    }
    setTime(t);
    menu(abb, heapCert, n);
}


void change(Objeto * abb, Objeto * heapCert, int n){
    int i;
    double v;
    printf("Digite o ponto e a velocidade a ser alterada: ");
    scanf("%d %lf", &i, &v);
    abb[i].traj.b = (abb[i].traj.a - v)*getTime() + abb[i].traj.b;
    abb[i].traj.a = v;
    if(i > 0) atualizaCertificado(abb, heapCert, abb[i].posicao, n);
    if(i < n-1) atualizaCertificado(abb, heapCert, abb[i+1].posicao, n);
    printf("O ponto %d agora se desloca com velocidade %g\n", i, v);
    menu(abb, heapCert, n);
}

void query(Objeto * abb, Objeto * heapCert, int n){
    int i;
    printf("Digite o ponto que deseja consultar: ");
    scanf("%d", &i);
    predecessor(i);
    menu(abb, heapCert, n);
}

void carregarArquivo(Objeto * abb, Objeto * heapCert, int n){
    FILE * arquivo;
    int i = 0;
    char nomeDoArquivo[80];
    printf("Digite o nome do arquivo: ");
    scanf("%s", nomeDoArquivo);

    arquivo = fopen(nomeDoArquivo, "r");
    fscanf(arquivo, "%d\n", &n);
    abb = criaabb(n);
    for(i = 0; i < n; i++){
      fscanf(arquivo, "%lf %lf",&(abb[i].traj.a), &(abb[i].traj.b));
      abb[i].valor = abb[i].traj.b;
    }
    fclose(arquivo);
    heapCert = iniciaHeap(n-1);
    iniciaCertificados(abb, heapCert, n);
    db(for(i = 1; i < n; i++){
        printf("Certificado referente ao ponto %d vence em %g, indice do certificado: %d\n", (heapCert[i].posicao)->indice, heapCert[i].valor, i);
    });
    constroiHeap(heapCert, n-1, 0);
    menu(abb, heapCert, n);
}