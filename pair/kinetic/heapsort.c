#include"heapsort.h"

double valueHeapsort(Point **v, int i, int dir){
    return getX(v[i], dir);
}

int compareH(Point **v, int i, int j, int dir){
    Point * a, * b;
    double x, y, vxa, vxb, aux;
    a = v[i];
    b = v[j];
    x = getX(a, dir);
    y = getX(b, dir);
    if(mod(x - y) < EPS){
        // vxa = getVx(a, dir);
        // vxb = getVx(b, dir);
        // aux = max(mod(vxa), mod(vxb));
        // vxa -= aux;
        // vxb -= aux;
        // if(mod(vxa - vxb) < EPS){
            // if they've the same x-speed use y-coordinate
            return getY(a, dir) < getY(b, dir) - EPS;
        //}
        return vxa < vxb - EPS;
    }
    return x - y > EPS;
    /* return (valueHeapsort(v, i, dir) > valueHeapsort(v, j, dir) + EPS); */
}

void swapHeapsort(int i, int j, Point ** v){
    Point *aux;
    aux = v[i];
    v[i] = v[j];
    v[j] = aux;
}

void sinkHeap(Point **v, int i, int m, int dir){
    int s = 2*i, p = i;
    double x = valueHeapsort(v, i, dir);
    Point * aux = v[i];

    while(s <= m){
        if(s < m && compareH(v, s, s + 1, dir))
            s += 1;
        if(x < valueHeapsort(v, s, dir) - EPS)
            break;
        v[p] = v[s];

        p = s;
        s = 2*p;
    }

    v[p] = aux;

}

void heapsort(Point ** v, int dir){
    int i;

    for(i = n/2; i >= 1; i--){
        sinkHeap(v, i, n, dir);
    }

    for(i = n; i > 1; i--){
        swapHeapsort(1, i, v);
        sinkHeap(v, 1, i-1, dir);
    }
}