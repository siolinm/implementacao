#include"pq.h"
int m = 0;
int maxsize = INITIAL_SIZE;

void initPQ(){
    int i;
    m = n;

    for(i = m/2; i >= 1; i--){
        sieve(i, m);             
    }
}

void insertPQ(Object * obj){
    int i;
    if(m + 1 == maxsize){
        Object ** W = malloc(2*maxsize*sizeof(*W));
        for(i = 1; i <= m; i++)
            W[i] = Q[i];
        
        free(Q);
        Q = W;
        maxsize = 2*maxsize;
    }
    Q[++m] = obj;
    obj->pqpos = m;
    updatePQ(obj, obj->certificate);
}

void deletePQ(Object * obj){
    int i = obj->pqpos;
    Q[i] = Q[m--];
    sieve(i, m);
}

Object * minPQ(){
    return Q[1];
}

double valuePQ(int i){
    return Q[i]->certificate;
}

void updatePQ(Object * obj, double t){
    int pai, j;
    double x;
    obj->certificate = t;
    j = obj->pqpos;
    pai = j;
    x = valuePQ(j);
    while(pai/2 >= 1 && x < valuePQ(pai/2)){
        Q[pai] = Q[pai/2];
        Q[pai/2]->pqpos = pai;
        pai = pai/2;
    }
    Q[pai] = obj;
    obj->pqpos = pai;
    sieve(pai, m);
}

void sieve(int i, int m){
    int filho = 2*i, pai = i;
    Object * x = Q[i];
    while(filho <= m){
        if(filho < m && valuePQ(filho) > valuePQ(filho + 1)) 
            filho += 1;
        if(x->certificate < valuePQ(filho)) 
            break;

        Q[pai] = Q[filho];
        Q[pai]->pqpos = pai;        
        pai = filho; filho = 2*pai;
    }
    Q[pai] = x;
    x->pqpos = pai;
}

void printPQ(char * prefix, int size, int idx, int b){
	int i;
    char * newprefix;
    if(prefix == NULL){
        prefix = malloc(sizeof(*prefix));
        prefix[0] = '\0';
    }
    if(idx <= m)
    {
        for(i = 0; prefix[i] != '\0'; i++)
            printf("%c", prefix[i]);

        if(b) 
            printf("├──"); 
        else 
            printf("└──" );
        /*printf("%d: %g*t + %g = %g\n", Q[idx]->id, Q[idx]->speed, Q[idx]->initv, value(Q[idx]));*/
        printf("%g\n", Q[idx]->certificate);        
		
        newprefix = malloc((size + 4)*sizeof(*newprefix));
        for(i = 0; i < size; i++)
            newprefix[i] = prefix[i];
        if(b)
            newprefix[size - 1] = '|';
        else
            newprefix[size - 1] = ' ';
        for(i = size; i < size + 4; i++)
            newprefix[i] = ' ';        
        newprefix[size + 3] = '\0';
		printPQ(newprefix, size + 4, 2*idx, 1);
        printPQ(newprefix, size + 4, 2*idx + 1, 0);
        
    }
    if(!b)
        free(prefix);
}