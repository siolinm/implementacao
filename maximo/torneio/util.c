#include"util.h"
#include"time.h"

void init(int m){
    n = m;
    cert = malloc(n*sizeof(*cert));
    torneio = malloc((n + 1)*sizeof(*torneio));
    x0 = malloc((n + 1)*sizeof(*x0));
    speed = malloc((n + 1)*sizeof(*speed));
    Q = malloc((n + 1)*sizeof(*Q));
    indQ = malloc((n + 1)*sizeof(*indQ));
    indT = malloc((n + 1)*sizeof(*indT));
}

void destroy(){
    free(cert);
    free(torneio);
    free(x0);
    free(speed);
    free(Q);
    free(indQ);
    free(indT);
}

double valor(int i){
    i = torneio[i];
    return x0[i] + speed[i]*getTime();
}

void printT(){
    int i;
    for(i = 1; i <= 2*n - 1; i++)
            printf("torneio[%d] = %d\n", i, torneio[i]);

    printf("\n");
}

void printPQ(){
    int i;
    for(i = 1; i <= n-1; i++)
        printf("Q[%d] = %d\n", i, Q[i]);

    printf("\n");
}

void printIQ(){
    int i;
    for(i = 1; i <= n-1; i++)
        printf("indQ[%d] = %d\n", i, indQ[i]);

    printf("\n");
}

void printIT(){
    int i;
    for(i = 1; i <= n; i++)
        printf("indT[%d] = %d\n", i, indT[i]);

    printf("\n");
}

void printC(){
    int i;
    for(i = 2; i <= n; i++)
        printf("cert[%d] = %g\n", i, cert[i]);

    printf("\n");
}

void swapTorneio(int i, int j){
    int aux = torneio[i];
    torneio[i] = torneio[j];
    torneio[j] = aux;
    indT[torneio[i]] = j;
    indT[torneio[j]] = i; 
}