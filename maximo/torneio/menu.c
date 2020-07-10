#include"menu.h"
#include"debug.h"

void carregarArquivo(){
    FILE * arquivo;
    int i = 0, j;
    char nomeDoArquivo[80];
    printf("Digite o nome do arquivo: ");
    scanf("%s", nomeDoArquivo);

    arquivo = fopen(nomeDoArquivo, "r");
    fscanf(arquivo, "%d\n", &n);
    init(n);
    for(i = 1, j = 2*n - 1; i <= n; i++, j--){
        fscanf(arquivo, "%lf %lf", &(speed[i]), &(x0[i]));
        torneio[j] = i;        
    }
    
    fclose(arquivo);
    /* ordena sorted */
    initTorneio();
    db(printT());
    db(printIT());
    iniciaCertificados();
    db(printC());
    initPQ();
    db(printPQ());
    db(printIQ());
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
            db(printT());
            db(printIT());
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
    /* se mudar o >= para > mudar no evento tambem*/
    while(t >= proximoEvento()){
        setTime(proximoEvento());
        evento();
    }
    setTime(t);    
}

void change(){
    int i, j, filho;
    double newSpeed;
    printf("Digite o elemento e a velocidade a ser alterada: ");
    scanf("%d %lf", &i, &newSpeed);
    j = i;
    i = indT[j];
    x0[j] += (speed[j] - newSpeed)*getTime();
    speed[j] = newSpeed;
    
    filho = i;
    atualizaCertificado(torneio[filho]);
    while(2*i + 1 <= 2*n-1){
        if(torneio[i] == torneio[2*i]){
            filho = 2*i + 1;
            i = 2*i;
        }
        else{
            filho = 2*i;
            i = 2*i + 1;
        }
        atualizaCertificado(torneio[filho]);
    }
    printf("O elemento %d agora se desloca com velocidade %g\n", j, newSpeed);    
}

void query(){    
    printf("Elemento maximo: %d, valor maximo: %g\n", torneio[1], valor(1));    
}