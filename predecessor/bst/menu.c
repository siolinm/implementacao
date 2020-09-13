#include"menu.h"

void loadFile(){
    FILE * file;
    Object * obj;
    int i = 0;
    char filename[80];
    printf("Enter the file name: ");
    scanf("%s", filename);

    file = fopen(filename, "r");
    fscanf(file, "%d\n", &n);
    init(n);
    for(i = 1; i <= n; i++){
        obj = malloc(sizeof(*obj));
        fscanf(file, "%lf %lf", &(obj->speed), &(obj->initv));
        obj->id = lastID++;
        obj->prev = obj->next = NULL;
        Q[i] = obj;
        obj->pqpos = i;
        r = insertNode(r, obj);
        root = insertNodeQ(root, obj);
    }

    fclose(file);
    initCert(r);    
    initPQ();
}

int menu(){
    double start, end;
    char opt = 'x';    
    start = end = 0;
    while(opt != 's'){
        printf("--------------- MENU ---------------\n");
        printf("(a)dvance\n");
        printf("(c)hange trajectory\n");
        printf("(d)elete\n");
        printf("(i)nsert\n");
        printf("(l)oad file\n");
        printf("(n)ow\n");
        db(printf("(p)rint tree\n");)
        printf("(q)uery\n");
        printf("(s)top\n");
        printf("---------------      ---------------\n");
        printf(">>> ");        
        scanf(" %c", &opt);
        start = clock();
        if(opt == 's'){
            destroy();
            removeAll(r);
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
        db(else if(opt == 'p'){
            printf("---------------AVL TREE---------------\n");
            print(NULL, 1, r, 0);
            printf("\n\n");
            printf("---------------ID TREE---------------\n");
            printQ(NULL, 1, root, 0);
            printf("---------------PRIORITY QUEUE---------------\n");
            printPQ(NULL, 1, 1, 0);
            printf("---------------LINKED LIST---------------\n");
            printL();
        })
        else if(opt == 'c') 
            change();
        else if(opt == 'n') 
            printf("now: %g\n", getTime());
        else if(opt == 'l')
            loadFile();
        end = clock();        
        printf("The operation took %g seconds\n", (double)(end - start)/CLOCKS_PER_SEC);        
        if(opt != 's'){
            db(
                printf("Next event: %g\n", nextEvent());
            );
        }
    }

    return 0;
}

double nextEvent(){
    return minPQ()->certificate;
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

void insert(){
    Object * obj;
    double speed, initv;
    printf("Enter the speed and the element's value: ");
    scanf("%lf %lf", &speed, &initv);
    obj = malloc(sizeof(*obj));
    obj->prev = obj->next = NULL;
    obj->speed = speed;
    obj->initv = initv - speed*getTime();
    obj->id = lastID++;
    r = insertNode(r, obj);
    newCert(obj);
    root = insertNodeQ(root, obj);
    insertPQ(obj);
    update(obj->next);
    printf("The element has been created with an id: %d\n", obj->id);
}

void delete(){
    int id;
    Object * obj, * next;
    printf("Enter the object ID: ");
    scanf("%d", &id);
    obj = queryQ(root, id);
    next = obj->next;
    r = deleteNode(r, obj);
    root = deleteNodeQ(root, obj);
    deletePQ(obj);
    destroyObject(obj);
    update(next);
}

void query(){
    int i;
    Object * obj;
    printf("Enter the position: ");
    scanf("%d", &i);
    obj = query_kth(r, i);
    printf("The %d-th element has an id: %d\n", i, obj->id);
}

void change(){
    Object * obj;
    int id;
    double newSpeed;
    printf("Enter the element and the new speed: ");
    scanf("%d %lf", &id, &newSpeed);
    obj = queryQ(root, id);    
    obj->initv += (obj->speed - newSpeed)*getTime();
    obj->speed = newSpeed;
    update(obj);
    update(obj->next);
    printf("The element %d now has a speed of %g\n", id, newSpeed);    
}