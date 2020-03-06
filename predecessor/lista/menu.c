#include"menu.h"
#include"time.h"
#include"util.h"
#include"lista.h"
#include"certificados.h"
#include"debug.h"
#include<stdio.h>

int menu(Objeto * lista, Objeto * heapCert, int n){
    char opt;
    printf("(a)vancar\n");
    printf("(c)arregar arquivo\n");
    printf("(m)udar trajetoria\n");
    printf("(p)arar\n");
    printf("(q)uery\n");
    printf(">>> ");
    scanf(" %c", &opt);
    if(opt == 'p'){
        if(lista) free(lista);
        if(heapCert) free(heapCert);
        return (0);
    } 
    if(opt == 'q') query(lista, heapCert, n);
    if(opt == 'a') avancar(lista, heapCert, n);
    if(opt == 'm') change(lista, heapCert, n);
    if(opt == 'c') carregarArquivo(lista, heapCert, n);

    return 0;
}

void avancar(Objeto * lista, Objeto * heapCert, int n){
    double t;
    printf("Digite o novo valor do tempo: ");
    scanf("%lf", &t);
    while(t > proximoEvento(heapCert)){
        setTime(proximoEvento(heapCert));
        evento(lista, heapCert, n);
    }
    setTime(t);
    menu(lista, heapCert, n);
}


void change(Objeto * lista, Objeto * heapCert, int n){
    int i;
    double v;
    printf("Digite o ponto e a velocidade a ser alterada: ");
    scanf("%d %lf", &i, &v);
    lista[i].traj.b = (lista[i].traj.a - v)*getTime() + lista[i].traj.b;
    lista[i].traj.a = v;
    if(i > 0) atualizaCertificado(lista, heapCert, lista[i].posicao, n);
    if(i < n-1) atualizaCertificado(lista, heapCert, lista[i+1].posicao, n);
    printf("O ponto %d agora se desloca com velocidade %g\n", i, v);
    menu(lista, heapCert, n);
}

void query(Objeto * lista, Objeto * heapCert, int n){
    int i;
    printf("Digite o ponto que deseja consultar: ");
    scanf("%d", &i);
    predecessor(i);
    menu(lista, heapCert, n);
}

void carregarArquivo(Objeto * lista, Objeto * heapCert, int n){
    FILE * arquivo;
    int i = 0;
    char nomeDoArquivo[80];
    printf("Digite o nome do arquivo: ");
    scanf("%s", nomeDoArquivo);

    arquivo = fopen(nomeDoArquivo, "r");
    fscanf(arquivo, "%d\n", &n);
    lista = criaLista(n);                
    for(i = 0; i < n; i++){
      fscanf(arquivo, "%lf %lf",&(lista[i].traj.a), &(lista[i].traj.b));
      lista[i].valor = lista[i].traj.b;  
    } 
    fclose(arquivo);
    qsort(lista, n, sizeof(*lista), compare);    
    heapCert = iniciaHeap(n-1);
    iniciaCertificados(lista, heapCert, n);
    db(for(i = 1; i < n; i++){
        printf("Certificado referente ao ponto %d vence em %g, indice do certificado: %d\n", (heapCert[i].posicao)->indice, heapCert[i].valor, i);
    });
    constroiHeap(heapCert, n-1, 0);
    menu(lista, heapCert, n);
}