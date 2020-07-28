#include"menu.h"
#include"tempo.h"
#include"util.h"
#include"certificados.h"
#include"debug.h"
#include<stdio.h>
#include<bits/time.h>
#include<time.h>

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
        trivial[i] = i;
        indS[i] = i;
    }
    
    fclose(arquivo);    
    heapsort();
    db(printS());
    iniciaCertificados();
    db(printC());
    initPQ();
    db(printPQ());
}

int menu(){
    char opt = 'x';
    int * aux;
    int correto, i;
    double start, end;
    start = end = 0;
    while(opt != 'p'){
        printf("--------------- MENU ---------------\n");
        printf("(a)vancar\n");
        printf("(c)arregar arquivo\n");
        printf("con(f)erir\n");
        printf("(m)udar trajetoria\n");
        printf("(n)ow\n");
        printf("(p)arar\n");
        printf("(q)uery\n");
        printf("query solucao (t)rivial\n");
        printf("---------------      ---------------\n");
        printf(">>> ");
        scanf(" %c", &opt);
        start = clock();
        if(opt == 'p')
            destroy();
        else if(opt == 'q')
            query();
        else if(opt == 'a') 
            advance();
        else if(opt == 'm') 
            change();
        else if(opt == 't') 
            queryTrivial();
        else if(opt == 'n') 
            printf("now: %g\n", getTime());
        else if(opt == 'c')
            carregarArquivo();
        else if(opt == 'f'){
            aux = sorted;
            sorted = trivial;
            heapsort();
            sorted = aux;
            correto = 1;
            for(i = 1; i <= n && correto; i++)                
                correto = (valor(sorted[i]) == valor(trivial[i]));
            if(!correto)
                printf("Nao ");
            printf("correto\n");
        }
        end = clock();        
        printf("A operacao levou %g segundos\n", (double)(end - start)/CLOCKS_PER_SEC);        
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
    printf("Digite o elemento e a velocidade a ser alterada: ");
    scanf("%d %lf", &i, &newSpeed);
    j = i;
    i = indS[j];
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

void queryTrivial(){
    int * aux = sorted;
    sorted = trivial;
    heapsort();
    query();
    sorted = aux;
}
