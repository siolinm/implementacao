#include"menu.h"
#include"heap.h"
#include"certificados.h"
#include"debug.h"
#include"pq.h"
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
        heap[i] = i;
        indH[i] = i;
    }
    
    fclose(arquivo);
    /* ordena sorted */
    initHeap();
    db(printH());
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
        printf("(n)ow\n");
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
        else if(opt == 'n') 
            printf("now: %g\n", getTime());
        else if(opt == 'c')
            carregarArquivo();
        if(opt != 'p'){
            db(printPQ());
            db(printIQ());
            db(printC());
            db(printH());
            db(printIH());
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
    i = indH[j];
    x0[j] += (speed[j] - newSpeed)*getTime();
    speed[j] = newSpeed;
    atualizaCertificado(i);
    atualizaCertificado(2*i);
    atualizaCertificado(2*i + 1);
    printf("O elemento %d agora se desloca com velocidade %g\n", j, newSpeed);    
}

void query(){    
    printf("Elemento maximo: %d, valor maximo: %g\n", heap[1], valor(1));    
}