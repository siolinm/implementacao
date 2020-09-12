#include"menu.h"

void loadFile(){
    FILE * file;
    int i = 0;
    char filename[80];
    printf("Enter the file name: ");
    scanf("%s", filename);

    file = fopen(filename, "r");
    fscanf(file, "%d\n", &n);
    init(n);
    for(i = 1; i <= n; i++){
        fscanf(file, "%lf %lf", &(speed[i]), &(x0[i]));
        heap[i] = i;
        indH[i] = i;
    }
    
    fclose(file);
    /* sorts sorted */
    initHeap();
    db(printH());
    initCert();
    db(printC());
    initPQ();
    db(printPQ());
}

int menu(){
    char opt = 'x';
    while(opt != 's'){
        printf("--------------- MENU ---------------\n");
        printf("(a)dvance\n");
        printf("(c)hange trajectory\n");        
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
        else if(opt == 'a') 
            advance();
        else if(opt == 'c') 
            change();
        else if(opt == 'n') 
            printf("now: %g\n", getTime());
        else if(opt == 'l')
            loadFile();
        if(opt != 's'){
            db(printPQ());
            db(printIQ());
            db(printC());
            db(printH());
            db(printIH());
            db(
                printf("Next event: %g\n", nextEvent());
            );
        }
    }

    return 0;
}

double nextEvent(){
    return cert[minPQ()];
}

void advance(){
    double t;
    printf("Enter the new time value: ");    
    scanf(" %lf", &t);
    if(t < getTime())            
        printf("Time earlier than current time\n");

    while(t >= nextEvent()){
        setTime(nextEvent());
        event();
    }
    setTime(t);    
}

void change(){
    int i, j;
    double newSpeed;
    printf("Enter the element's id and the new speed: ");    
    scanf("%d %lf", &i, &newSpeed);
    j = i;
    i = indH[j];
    x0[j] += (speed[j] - newSpeed)*getTime();
    speed[j] = newSpeed;
    update(i);
    update(2*i);
    update(2*i + 1);

    printf("Element %d now has a speed of %g\n", j, newSpeed);    
}

void query(){    
    printf("Max element: %d, max value: %g\n", heap[1], value(1));
}