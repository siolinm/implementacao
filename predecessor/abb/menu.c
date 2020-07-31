#include"menu.h"
#include"tempo.h"
#include"util.h"
#include"queries.h"
#include"avl.h"
#include"pq.h"
#include"certificados.h"
#include"debug.h"
#include<stdio.h>
#include<bits/time.h>
#include<time.h>

void carregarArquivo(){
    FILE * arquivo;
    Object * obj;
    int i = 0;
    char nomeDoArquivo[80];
    printf("Digite o nome do arquivo: ");
    scanf("%s", nomeDoArquivo);

    arquivo = fopen(nomeDoArquivo, "r");
    fscanf(arquivo, "%d\n", &n);
    init(n);
    for(i = 1; i <= n; i++){
        obj = malloc(sizeof(*obj));
        fscanf(arquivo, "%lf %lf", &(obj->speed), &(obj->initv));
        obj->id = lastID++;
        Q[i] = obj;
        raiz = insereNo(raiz, obj);
    }

    fclose(arquivo);    
    iniciaCertificados(raiz);    
    initPQ();
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
        printf("(d)eletar elemento\n");
        printf("(i)nserir elemento\n");
        printf("(m)udar trajetoria\n");
        printf("(n)ow\n");
        printf("(p)arar\n");
        printf("(q)uery\n");
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
        else if(opt == 'i') 
            insert();
        else if(opt == 'd') 
            delete();
        else if(opt == 'm') 
            change();
        else if(opt == 'n') 
            printf("now: %g\n", getTime());
        else if(opt == 'c')
            carregarArquivo();
        end = clock();        
        printf("A operacao levou %g segundos\n", (double)(end - start)/CLOCKS_PER_SEC);        
        if(opt != 'p'){
            db(
                printf("Proximo evento: %g\n", proximoEvento());
            );
        }
    }

    return 0;
}

double proximoEvento(){
    return minPQ()->certificate;
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

void insert(){
    Object * obj;
    double speed, initv;
    printf("Digite a velocidade e o valor inicial do elemento (no instante atual): ");
    scanf("%lf %lf", &speed, &initv);
    obj = malloc(sizeof(*obj));
    obj->speed = speed;
    obj->initv = initv - speed*getTime();
    obj->id = lastID++;
    raiz = insereNo(raiz, obj);
    root = insereNoQ(root, obj);
    insertPQ(obj);
    printf("O elemento foi criado com id: %d\n", obj->id);
}

void delete(){
    int id;
    Object * obj;
    printf("Digite o ID do objeto a ser deletado: ");
    scanf("%d", &id);
    obj = queryQ(root, id);
    raiz = deleteNo(raiz, obj);
    root = deleteNoQ(root, obj);
    deletePQ(obj);    
    destroyObject(obj);
}

void query(){
    int i;
    Object * obj;
    printf("Digite a posicao que deseja consultar: ");
    scanf("%d", &i);
    obj = queryKth(raiz, i);
    printf("O i-esimo elemento tem id: %d\n", obj->id);
}

void change(){
    Object * obj;
    int id;
    double newSpeed;
    printf("Digite o id do elemento e a velocidade a ser alterada: ");
    scanf("%d %lf", &id, &newSpeed);
    obj = queryQ(root, id);    
    obj->initv += (obj->speed - newSpeed)*getTime();
    obj->speed = newSpeed;
    update(obj);
    update(obj->prev);
    printf("O elemento %d agora se desloca com velocidade %g\n", id, newSpeed);    
}