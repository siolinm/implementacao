#include"menu.h"
#include"debug.h"

void initialInsert(Point * p){
    int i;
    initial[lastID++] = p;

    for(i = 0; i < 3; i++){        
        p->cands[i] = NULL;
        p->candsRoot[i] = initCands(p, i);
        p->hitsLow[i] = NULL;
        p->hitsUp[i] = NULL;
        p->hitsLowRoot[i] = initHits(p, i);
        p->hitsUpRoot[i] = initHits(p, i);
        p->id = lastID - 1;
        p->lastMatch[i] = -1;
        p->listPosition[i] = NULL;
        p->next[i] = NULL;
        p->prev[i] = NULL;               
    }
}

void init(int m){
    initial[m] = initial[0];
    listInit();
    initPQ();
    initCertTourn(HORIZONTAL);
    initMaxima(HORIZONTAL);
    initCandsHits(HORIZONTAL);
}

void loadFile(){
    FILE * file;
    Object * obj;
    int i = 0, j;
    char filename[80];
    printf("Enter the file name: ");
    scanf("%s", filename);

    file = fopen(filename, "r");
    fscanf(file, "%d\n", &n);
    initial = malloc((n + 1)*sizeof(*initial));

    for(i = 1, j = 2*n - 1; i <= n; i++, j--){
        obj = malloc(sizeof(*obj));
        fscanf(file, "%lf %lf %lf %lf", &(obj->x0.x), &(obj->x0.y), &(obj->speed.x), &(obj->speed.y));
        obj->id = lastID++;
        initialInsert(obj);
    }
    init(n);      
    
    fclose(file);
}

int main(){
    Coordinate p;
    Vector v;
    double t;
    int j;
    char opt = 'x';
    while(opt != 's'){
        printf("--------------- MENU ---------------\n");
        printf("(a)dvance\n");
        printf("(c)hange trajectory\n");
        printf("(d)elete\n");
        printf("(i)nsert point\n");
        printf("(l)oad file\n");
        printf("(n)ow\n");
        printf("(q)uery\n");
        printf("(s)top\n");
        printf("---------------      ---------------\n");
        printf(">>> ");
        scanf(" %c", &opt);
        if(opt == 's')
            destroy();
        else if(opt == 'q')
            query();
        else if(opt == 'a') {
            printf("Enter the new time value: ");
            scanf(" %lf", &t);
            advance(t);
        }
        else if(opt == 'c') {
            printf("Enter the element id and the new speed: ");
            scanf("%d %lf %lf", &j, &v.x, &v.y);
            change(j, v);
        }
        else if(opt == 'i') {
            printf("Enter the position and the element speed: ");
            scanf("%lf %lf %lf %lf", &p.x, &p.y, &v.x, &v.y);
            insert(p, v);
        }
        else if(opt == 'd'){
            printf("Enter the object ID: ");
            scanf("%d", &j);
            delete(j);
        }
        else if(opt == 'n') 
            printf("now: %g\n", now);
        else if(opt == 'l')
            loadFile();
        if(opt != 's'){            
            db(
                printf("Next event: %g\n", nextEvent());
            );
        }
    }

    return 0;
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

}