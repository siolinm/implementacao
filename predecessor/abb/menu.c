#include"menu.h"
#include"time.h"
#include"util.h"
#include"certificados.h"
#include"avl.h"
#include"listapontos.h"
#include"debug.h"
#include<stdio.h>


/* OK */
int menu(Objeto * raiz, Objeto * heapCert, int n){
    char opt;
    printf("(a)vancar\n");
    printf("(c)arregar arquivo\n");
    printf("(i)nsere ponto\n");
    printf("(d)eleta ponto\n");
    printf("(m)udar trajetoria\n");
    printf("(p)arar\n");
    printf("(q)uery\n");
    printf(">>> ");
    scanf(" %c", &opt);
    if(opt == 'p'){
        if(heapCert) free(heapCert);
        return (0);
    } 
    if(opt == 'q') query(raiz, heapCert, n);
    if(opt == 'a') avancar(raiz, heapCert, n);
    if(opt == 'm') change(raiz, heapCert, n);
    if(opt == 'c') carregarArquivo(raiz, heapCert, n);

    return 0;
}

/* OK */
void avancar(Objeto * raiz, Objeto * heapCert, int n){
    double t;
    printf("Digite o novo valor do tempo: ");
    scanf("%lf", &t);
    while(t > proximoEvento(heapCert)){
        setTime(proximoEvento(heapCert));
        evento();
    }
    setTime(t);
    menu(raiz, heapCert, n);
}

/* +- OK, problema: identificador para o ponto */
void change(Objeto * raiz, Objeto * heapCert, int n){
    int i;
    double v;
    Objeto * ponto;
    printf("Digite o ponto e a velocidade a ser alterada: ");
    scanf("%d %lf", &i, &v);
    ponto = getPonto(i);
    
    ponto->traj.b = (ponto->traj.a - v)*getTime() + ponto->traj.b;
    ponto->traj.a = v;
    if(ponto->predecessor) atualizaCertificado(ponto->posicao);
    if(ponto->sucessor) atualizaCertificado(ponto->sucessor->posicao);    
    printf("O ponto %d agora se desloca com velocidade %g\n", i, v);
    menu(raiz, heapCert, n);
}

/* +- OK, problema: identificador para o ponto */
void query(Objeto * raiz, Objeto * heapCert, int n){
    int i;
    printf("Digite o ponto que deseja consultar: ");
    scanf("%d", &i);
    predecessor(i);
    menu(raiz, heapCert, n);
}


/* !OK */
void carregarArquivo(Objeto * raiz, Objeto * heapCert, int n){
    FILE * arquivo;
    int i = 0;
    char nomeDoArquivo[80];
    printf("Digite o nome do arquivo: ");
    scanf("%s", nomeDoArquivo);

    arquivo = fopen(nomeDoArquivo, "r");
    fscanf(arquivo, "%d\n", &n);
    Objeto * ponto = malloc(sizeof(Objeto));
    for(i = 0; i < n; i++){
      fscanf(arquivo, "%lf %lf",&(ponto->traj.a), &(ponto->traj.b));
      ponto->valor = ponto->traj.b;
      inserePonto(ponto);
    }
    fclose(arquivo);
    /*
    heapCert = iniciaHeap(n-1);
    iniciaCertificados(raiz, heapCert, n);
    db(for(i = 1; i < n; i++){
        printf("Certificado referente ao ponto %d vence em %g, indice do certificado: %d\n", (heapCert[i].posicao)->indice, heapCert[i].valor, i);
    });
    constroiHeap(heapCert, n-1, 0);
    menu(raiz, heapCert, n);*/
}