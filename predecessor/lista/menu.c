#include"menu.h"
#include"time.h"
#include"util.h"
#include"heapsort.h"
#include"certificados.h"
#include"debug.h"
#include<stdio.h>

void carregarArquivo(){
    FILE * arquivo;
    int i = 0;
    char nomeDoArquivo[80];
    printf("Digite o nome do arquivo: ");
    scanf("%s", nomeDoArquivo);

    arquivo = fopen(nomeDoArquivo, "r");
    fscanf(arquivo, "%d\n", &n);
    init(n);
    for(i = 1; i <= n; i++){
        fscanf(arquivo, "%lf %lf", &(speed[i]), &(x0[i]));
        sorted[i] = i;
    }
    
    fclose(arquivo);
    /* ordena sorted */
    heapsort();
    db(printS());
    iniciaCertificados();
    db(printC());
    initPQ();
    db(printPQ());
}

int menu(){
    char opt = 'x';
    while(opt != 'p'){
        printf("--------------- MENU ---------------\n");
        printf("(a)vancar\n");
        printf("(c)arregar arquivo\n");
        printf("(m)udar trajetoria\n");
        printf("(p)arar\n");
        printf("(q)uery\n");
        printf("---------------      ---------------\n");
        printf(">>> ");
        scanf(" %c", &opt);
        if(opt == 'p')
            destroy();
        else if(opt == 'q')
            query();
        else if(opt == 'a') 
            advance();
        else if(opt == 'm') 
            change();
        else if(opt == 'c')
            carregarArquivo();
        if(opt != 'p'){
            db(printPQ());
            db(printIQ());
            db(printC());
            db(printS());
            db(
                printf("Proximo evento: %g\n", proximoEvento());
            );
        }
    }

    return 0;
}

double proximoEvento(){
    return cert[minPQ()];
}

void advance(){
    double t;
    printf("Digite o novo valor do tempo: ");
    scanf(" %lf", &t);
    if(t < getTime())
        printf("Unidade de tempo inferior ao instante atual\n");
    while(t >= proximoEvento()){
        setTime(proximoEvento());
        evento();
    }
    setTime(t);    
}

void change(){
    int i, j;
    double newSpeed;
    printf("Digite o ponto e a velocidade a ser alterada: ");
    scanf("%d %lf", &i, &newSpeed);
    j = sorted[i];
    x0[j] += (speed[j] - newSpeed)*getTime();
    speed[j] = newSpeed;
    atualizaCertificado(i);
    atualizaCertificado(i - 1);
    printf("O elemento %d agora se desloca com velocidade %g\n", j, newSpeed);    
}

void predecessor(int i){
    if(i >= 1 && i < n)
        printf("O predecessor do elemento %d e' o elemento %d\n", sorted[i], sorted[i + 1]);
    else
        printf("A posicao indicada nao possui predecessor\n");
}

void query(){
    int i;
    printf("Digite a posicao que deseja consultar: ");
    scanf("%d", &i);
    predecessor(i);    
}