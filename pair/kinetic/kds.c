#include "kds.h"

void sendPoint(Point * p){
    int i;
    initial[lastID++] = p;

    p->id = lastID - 1;
    
    for(i = 0; i < 3; i++){        
        p->cands[i] = NULL;
        p->hitsLow[i] = NULL;
        p->hitsUp[i] = NULL;
        p->lcand[i] = NULL;

        initS(p, CANDS_TREE, i);  
        initS(p, HITS_LOW_TREE, i);
        initS(p, HITS_UP_TREE, i);

        p->lastMatch[i] = -1;
        /* */
        p->listPosition[i] = NULL;
        p->next[i] = NULL;
        p->prev[i] = NULL;
        listInsert(p, i);
    }
}

void initKDS(){
    initial = malloc((n + 1)*sizeof(*initial));
    lastID = 0;
    now = 0;
    listInit();
    initPQ();
    /* initTourn(n); */
    initTourn(3*n);
}

void buildKDS(){
    int i;
    initial[n] = initial[0];
    initial[0] = NULL;
        
    initMaxima(HORIZONTAL);
    initCandsHits(HORIZONTAL);
    for(i = 1; i <= n; i++)
        sendTourn(initial[i], HORIZONTAL);
   
            
    initMaxima(UP);
    initCandsHits(UP);
    for(i = 1; i <= n; i++)
        sendTourn(initial[i], UP);   
    
    initMaxima(DOWN);
    initCandsHits(DOWN);
    for(i = 1; i <= n; i++)
        sendTourn(initial[i], DOWN);
   
    buildTourn();    
    /* free(initial); */
}

double nextEvent(){
    return minPQ()->p->cert[minPQ()->certType]->value;
}

void advance(double t){        
    if(t < now)
        printf("Time earlier than current time\n");
    
    while(t >= nextEvent()){
        now = nextEvent();
        event();
    }
    now = t;
}

void change(int j, Vector v){
   
}

void insert(Coordinate xt, Vector v){
    
}

void delete(int i){

}

void query(){
    TournObject * a = tourn[1];
    char name = (a->lcandp ? a->lcandp->name : '-');
    printf("Closest pair: %c -- %c: %g\n", a->p->name, name, distance(a->p, a->lcandp, a->direction));
}

Vector getVector(int dir, int order){
    Vector v;
    double angle = 0;
    if(dir == UP)
        angle += PI_3;
    else if(dir == DOWN)
        angle -= PI_3;
    if(order == UP)
        angle += PI_3/2;
    else if(order == DOWN)
        angle -= PI_3/2;
    v.x = cos(angle);
    v.y = sin(angle);
    return v;
}

void drawEdges(Point * p, int dir){
    Point * up, * low;
    Coordinate a, b;
    double alpha;
    int rot = 160;
    const double norm = 6.0;
    Vector v1 = getVector(dir, UP);
    Vector v2 = getVector(dir, DOWN);
    a.x = getX(p, HORIZONTAL);
    a.y = getY(p, HORIZONTAL);
    if(dir == UP) rot = 330;
    else if(dir == DOWN) rot = 120;
    printf("\\node[label={[label distance = -3mm]%d:$%c$}]"
            "at (%.3lf, %.3lf) {\\textbullet};\n", rot, p->name, a.x, a.y);
    printf("%% %c up edge\n", p->name);
    up = ownerS(p->hitsUp[dir], HITS_UP_TREE, dir);
    if(up == NULL){
        b.x = a.x + norm*v1.x;
        b.y = a.y + norm*v1.y;
    }
    else{
        b.x = getX(up, HORIZONTAL);
        b.y = getY(up, HORIZONTAL);
        alpha = (b.y - a.y)*v2.x - v2.y*(b.x - a.x);
        alpha /= -v1.x*v2.y + v2.x*v1.y;

        b.x = a.x + alpha*v1.x;
        b.y = a.y + alpha*v1.y;
    }
    printf("\\draw (%.3lf, %.3lf) -- (%.3lf, %.3lf);\n", a.x, a.y, b.x, b.y);
    v1 = getVector(dir, DOWN);
    v2 = getVector(dir, UP);
    printf("%% %c down edge\n", p->name);
    low = ownerS(p->hitsLow[dir], HITS_LOW_TREE, dir);
    if(low == NULL){
        b.x = a.x + norm*v1.x;
        b.y = a.y + norm*v1.y;
    }
    else{
        b.x = getX(low, HORIZONTAL);
        b.y = getY(low, HORIZONTAL);
        alpha = (b.y - a.y)*v2.x - v2.y*(b.x - a.x);
        alpha /= -v1.x*v2.y + v2.x*v1.y;

        b.x = a.x + alpha*v1.x;
        b.y = a.y + alpha*v1.y;
    }
    printf("\\draw (%.3lf, %.3lf) -- (%.3lf, %.3lf);\n", a.x, a.y, b.x, b.y);
}

void draw(){
    int i, dir;
    printf("Which direction? (0 - horizontal, 1 - up, 2 - down) ");
    scanf("%d", &dir);

    if(dir == 0)
        dir = HORIZONTAL;
    else if(dir == 1)
        dir = UP;
    else 
        dir = DOWN;

    for(i = 1; i <= n; i++)
        drawEdges(initial[i], dir);
}

void showInfo(){
    int i, j;
    for (i = 0; i < 3; i++)
        printList(i);
    printTourn();
    for(j = 0; j < 3; j++){
        for(i = 1; i <= n; i++){
            printPoint(initial[i], j);
            printf("\n");
        }
        printf("\n\n");
    }
}

void test(){
    int i, j, x, y;
    double dmin = distance(initial[1], initial[2], HORIZONTAL);
    x = 1;
    y = 2;
    for(i = 1; i <= n; i++)
        for(j = i + 1; j <= n; j++){
            if(distance(initial[i], initial[j], HORIZONTAL) < dmin){
                x = i;
                y = j;
                dmin = distance(initial[i], initial[j], HORIZONTAL);
            }
        }

    printf("%c -- %c, distance: %.3lf\n", initial[x]->name, initial[y]->name, dmin);
}

void freeKDS(){
    free(initial);
}