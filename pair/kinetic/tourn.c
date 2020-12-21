#include"tourn.h"

int compareTourn(int i, int j){
    double a, b;
    a = distance(tourn[i]->p, tourn[i]->lcandp, tourn[i]->direction);
    b = distance(tourn[j]->p, tourn[j]->lcandp, tourn[j]->direction);
    return a < b;
}

void buildTourn(){
    int i;
    int dir;
    tournElem = 3*n;
    /*
    for(i = n; i >= 1; i--){
        tourn[n + i - 1] = initial[i];
    }
    */
    i = 2*tournElem - 1;
    while(i > 1){
        if(compareTourn(i, i - 1)){
            tourn[i/2] = tourn[i];
            dir = tourn[i-1]->direction;
            tourn[i - 1]->p->lastMatch[dir] = i - 1;
        }
        else{
            tourn[i/2] = tourn[i - 1];
            dir = tourn[i]->direction;
            tourn[i]->p->lastMatch[dir] = i;
        }

        i = i - 2;
    }

    dir = tourn[1]->direction;
    tourn[1]->p->lastMatch[dir] = 1;
}

/*
    minimum size has to be at least 2
*/
void resizeTourn(){
    int i;
    TournObject ** newTourn;
    newTourn = malloc((2*tournMaxSize + 1)*sizeof(*newTourn));

    for (i = 1; i <= 2*tournElem - 1; i++){
        newTourn[i] = tourn[i];
    }

    newTourn = tourn;
    tournMaxSize = 2*tournMaxSize;
}

void insertTourn(Point * p, int dir){
    int i, k;
    TournObject * obj;
    obj = malloc(sizeof(*obj));
    obj->p = p;
    obj->lcandp = p->lcand[dir];
    obj->direction = dir;

    if(2*tournElem + 1 == tournMaxSize)
        resizeTourn();
    tournElem++;

    i = 2*tournElem - 1;

    tourn[i] = obj;
    tourn[i - 1] = tourn[i/2];
    
    k = i - 1;

    while(i > 1 && compareTourn(i, k)){
        tourn[i/2] = tourn[i];
        dir = tourn[k]->p->lastMatch[dir];
        tourn[k]->p->lastMatch[dir] = k;
        updateTournCert(tourn[k]);
        
        i = i/2;
        k = 2*(i/2) + !(i % 2);
    }

    dir = tourn[i]->p->lastMatch[dir];
    tourn[i]->p->lastMatch[dir] = i;    
}

void deleteTourn(Point * p, int dir){
    int k, j, i;
    i = p->lastMatch[dir];

    /*
        Looks for the "first match" that obj played
    */
    j = i;
    k = 2*(j/2) + !(j % 2);

    if(2*j < 2*tournElem - 1){
        while(j < 2*tournElem - 1){
            if(j > 1 && tourn[j] != tourn[j/2])
                j = k;
            
            j = 2*j;
            k = 2*(j/2) + !(j % 2);
        }

        j = j/2;
        k = 2*(j/2) + !(j % 2);
    }

    /*
        Looks for a object to substitute the removed one.
        The object that will substitute the removed object is 
        the one who lost the match between the two last positions.
        If the object that is being removed is already at one of the two last positions
        remove the two last positions and make his brother go up
    */
    if(j == 2*tournElem - 1 || j == 2*tournElem - 2){
        tourn[j/2] = tourn[k];
        tourn[j] = tourn[k] = NULL;
        j = j/2;
        k = 2*(j/2) + !(j % 2);
    }
    else{
        if(tourn[2*tournElem - 1] == tourn[tournElem - 1])
            tourn[j] = tourn[2*tournElem - 2];
        else
            tourn[j] = tourn[2*tournElem - 1];

        tourn[2*tournElem - 1] = tourn[2*tournElem - 2] = NULL;
    }

    /*
        Goes up fixing matches, j is the winner and k is the loser of the match
    */
    while(j > 1){
        if(!compareTourn(j, k)){
            i = k;
            k = j;
            j = i;
        }

        tourn[j/2] = tourn[j];
        dir = tourn[k]->direction;
        tourn[k]->p->lastMatch[dir] = k;
        updateTournCert(tourn[k]);
        
        j = j/2;
        k = 2*(j/2) + !(j % 2);
    }

    dir = tourn[j]->direction;
    tourn[j]->p->lastMatch[dir] = j;
    updateTournCert(tourn[j]);
}

void initCertTourn(){
    int i;
    TournObject * a;    
    /* initializes tourn certificates */
    for(i = 2*tournElem - 1; i >= n; i--){
        a = tourn[i];
                
        newCertTourn(a);
    }
}


/* TODO: rewrite this */
/* 
 * assuming d(a, lcand(a)) <= d(b, lcand(b)) 
 * 
 * goal: t such that d(a, lcand(a)) >= d(b, lcand(b)) in [t, t + eps] eps > 0
 * 
 * (1)  (x(a) - x(lcand(a)))^2 + (y(a) - y(lcand(a)))^2 >= (x(b) - x(lcand(b)))^2 + (y(b) - y(lcand(b)))^2
 * 
 * x(a) = x_0(a) + t*speed(a).x
 * y(a) = y_0(a) + t*speed(a).y
 * 
 * let c_1 = speed(a).x - speed(lcand(a)).x
 * c_2 = x_0(a) - x_0(lcand(a))
 * c_3 = speed(a).y - speed(lcand(a)).y
 * c_4 = y_0(a) - y_0(lcand(a))
 * 
 * c_5, c_6, c_7 and c_8 are similar but to point b
 * 
 * Rewriting (1):
 * 
 * (tc_1 + c_2)^2 + (tc_3 + c_4)^2 >= (tc_5 + c_6)^2 + (tc_7 + c_8)^2
 * ....
 * t^2(c_1^2 + c_3^2 - c_5^2 - c_7^2) + 2t(c_1c_2 + c_3c_4 - c_5c_6 - c_7c_8) + c_2^2 + c_4^2 - c_6^2 - c_8^2 >= 0
 * 
 * m = (c_1^2 + c_3^2 - c_5^2 - c_7^2)
 * n = 2(c_1c_2 + c_3c_4 - c_5c_6 - c_7c_8)
 * o = c_2^2 + c_4^2 - c_6^2 - c_8^2
 * 
 * mt^2 + nt + o >= 0
 * 
 * Cases:
 * if m > 0, then n^2 - 4mo must be > 0
 * return is the bigger root
 * 
 * if m < 0 and n^2 - 4mo <= 0 return INF
 * 
 * if m < 0 and n^2 - 4mo > 0 return smaller root
 * 
 * if m = 0:
 *      nt + o >= 0
 * 
 *      n > 0 return -o/n
 * 
 *      n < 0 return INF
 *      
 *      if n = 0:
 *          o must be <= 0
 *          return INF
 * 
 */
double expireTourn(TournObject * a, TournObject * b){
    int i;
    TournObject * aux;
    double c[9], m, n, o, delta, t1, t2;
    if(a->lcandp == NULL || b->lcandp == NULL)
        return INFINITE;
    aux = a;
    for(i = 0; i < 2; i++){
        c[4*i + 1] = getVx(aux->p, aux->direction) - getVx(aux->lcandp, aux->direction);
        c[4*i + 2] = getX0(aux->p, aux->direction) - getX0(aux->lcandp, aux->direction);
        c[4*i + 3] = getVy(aux->p, aux->direction) - getVy(aux->lcandp, aux->direction);
        c[4*i + 4] = getY0(aux->p, aux->direction) - getY0(aux->lcandp, aux->direction);
        aux = b;
    }

    m = c[1]*c[1] + c[3]*c[3] - c[5]*c[5] - c[7]*c[7];
    n = 2*(c[1]*c[2] + c[3]*c[4] - c[5]*c[6] - c[7]*c[8]);
    o = c[2]*c[2] + c[4]*c[4] - c[6]*c[6] - c[8]*c[8];
    delta = n*n - 4*m*o;

    if(m > 0){
        if(delta <= 0){
            printf("Something gone wrong! Delta isn't positive\n");
        }
        else{
            t1 = -n + sqrt(delta);
            t1 = t1/2*m;
            t2 = -n - sqrt(delta);
            t2 = t2/2*m;

            if(t1 < t2)
                t1 = t2;
        }
    }
    else if (m < 0){
        if(delta <= 0)
            return INFINITE;
        
        t1 = -n + sqrt(delta);
        t1 = t1/2*m;
        t2 = -n - sqrt(delta);
        t2 = t2/2*m;

        if(t1 > t2)
            t1 = t2;
    }
    else{
        if(n > 0){
            t1 = -o/n;
        }
        else if(n < 0){
            t1 = INFINITE;
        }
        else{
            if(o > 0){
                printf("Something gone wrong! o > 0\n");
            }
            else{
                t1 = INFINITE;
            }
        }
    }

    return t1;
}


void newCertTourn(TournObject * obj){
    int i, dir;
    Cert * newCert = malloc(sizeof(*newCert));    

    dir = obj->direction;
    obj->p->cert[TOURN_CERT + dir] = newCert;
    i = obj->p->lastMatch[dir];

    if(i == 1){
        newCert->value = INFINITE;
    }
    else{
        newCert->value = expireTourn(tourn[i/2], tourn[i]);
    }

    insertPQ(obj->p, TOURN_CERT + dir);
}

void updateTournCert(TournObject * a){
    int i, dir;
    Cert *cert;
    dir = a->direction;
    cert = a->p->cert[TOURN_CERT + dir];

    dir = a->direction;
    i = a->p->lastMatch[dir];

    if(i == 1){
        cert->value = INFINITE;
        updatePQ(a->p, TOURN_CERT + dir, cert->value);
        return;
    }

    cert->value = expireTourn(tourn[i/2], tourn[i]);

    updatePQ(a->p, TOURN_CERT + dir, cert->value);
}