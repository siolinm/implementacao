#include"util.h"
#include"time.h"

void init(int m){
    n = m;
    cert = malloc((n - 1)*sizeof(*cert));
    sorted = malloc(n*sizeof(*sorted));
    x0 = malloc(n*sizeof(*x0));
    speed = malloc(n*sizeof(*speed));
    Q = malloc(n*sizeof(*Q));
    indQ = malloc(n*sizeof(*indQ));
}

void destroy(){
    free(cert);
    free(sorted);
    free(x0);
    free(speed);
    free(Q);
    free(indQ);
}

double valor(int i){
    return x0[i] + speed[i]*getTime();
}