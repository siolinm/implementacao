#include"menu.h"

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
        obj->prev = obj->next = NULL;
        Q[i] = obj;
        obj->pqpos = i;
        raiz = insereNo(raiz, obj);
        root = insereNoQ(root, obj);
    }

    fclose(arquivo);    
    iniciaCertificados(raiz);    
    initPQ();
}

int menu(){
    double start, end;
    char opt = 'x';    
    start = end = 0;
    while(opt != 'p'){
        printf("--------------- MENU ---------------\n");
        printf("(a)vancar\n");
        printf("(c)arregar arquivo\n");
        printf("(d)eletar elemento\n");
        db(printf("(e)xibir arvore\n");)
        printf("(i)nserir elemento\n");
        printf("(m)udar trajetoria\n");
        printf("(n)ow\n");
        printf("(p)arar\n");
        printf("(q)uery\n");
        printf("---------------      ---------------\n");
        printf(">>> ");
        scanf(" %c", &opt);
        start = clock();
        if(opt == 'p'){
            destroy();
            removeAll(raiz);
            removeAllQ(root);
        }
        else if(opt == 'q')
            query();
        else if(opt == 'a') 
            advance();
        else if(opt == 'i') 
            insert();
        else if(opt == 'd') 
            delete();
        db(else if(opt == 'e'){
            printf("---------------ARVORE DOS VALORES---------------\n");
            print(NULL, 1, raiz, 0);
            printf("\n\n");
            printf("---------------ARVORE DOS IDs---------------\n");
            printQ(NULL, 1, root, 0);
            printf("---------------FILA DE PRIORIDADE---------------\n");
            printPQ(NULL, 1, 1, 0);
            printf("---------------LISTA LIGADA---------------\n");
            printL();
        })
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
    obj->prev = obj->next = NULL;
    obj->speed = speed;
    obj->initv = initv - speed*getTime();
    obj->id = lastID++;
    raiz = insereNo(raiz, obj);
    criaCertificado(obj);
    root = insereNoQ(root, obj);
    insertPQ(obj);
    update(obj->next);
    printf("O elemento foi criado com id: %d\n", obj->id);
}

void delete(){
    int id;
    Object * obj, * prox;
    printf("Digite o ID do objeto a ser deletado: ");
    scanf("%d", &id);    
    obj = queryQ(root, id);
    prox = obj->next;
    raiz = deleteNo(raiz, obj);
    db(printf("deletei da primeira\n"));
    root = deleteNoQ(root, obj);
    deletePQ(obj);    
    destroyObject(obj);
    update(prox);
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
    update(obj->next);
    printf("O elemento %d agora se desloca com velocidade %g\n", id, newSpeed);    
}