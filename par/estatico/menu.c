#include"menu.h"
#include"debug.h"
void loadPoints(char mode){
    int i;
    if(mode == 'i')
        printf("Enter the number of points: ");
    scanf("%d", &n);

    init(n);

    for(i = 1; i <= n; i++){
        if(mode == 'i')
            printf("Enter the %d-th point coordinates: ", i);
        points[i] = malloc(sizeof(*(points[i])));
        scanf("%lf %lf %c", &(points[i]->x), &(points[i]->y), &(points[i]->nome));
    }
}

void draw(){
    int i = 0;
    Point * lcandp;
    Node * lcandsRoot;
    double minDistance = INFINITE, pdistance;
    root = NULL;
    for(i = 1; i <= n; i++)
        printf("\\node[label={[label distance = -3mm]160:$%c$}] at (%.2lf, %.2lf) {\\textbullet};\n",  points[i]->nome, points[i]->x, points[i]->y);
    printf("\n");
    angle = 0;
    heapsort();
    for(i = n; i >= 1; i--){                        
        lcandsRoot = cands(points[i]);            
        lcandp = lcand(lcandsRoot, NULL);
        insert(points[i]);
    }
    freeAll(root);
}

double closestDistance(){
    int i, j = 0;
    Point * lcandp;
    Node * lcandsRoot;
    double minDistance = INFINITE, pdistance;
    root = NULL;
    angle = -PI_3;
    while(j < 3){
        heapsort();
        for(i = n; i >= 1; i--){
            db(
                printf("--------------- (%g, %g) ---------------\n", points[i]->x, points[i]->y);
                print(NULL, 1, root, 0);
                printf("---------------          ---------------\n");
            );            
            lcandsRoot = cands(points[i]);
            db(
                printf("--------------- (%g, %g) ---------------\n", points[i]->x, points[i]->y);
                print(NULL, 1, root, 0);
                printf("---------------          ---------------\n");
            );
            lcandp = lcand(lcandsRoot, NULL);
            insert(points[i]);
            if(lcandp){
                pdistance = distance(points[i], lcandp);
                if(pdistance < minDistance)
                    minDistance = pdistance;
            }
        }
        angle += PI_3;
        freeAll(root);
        j++;
    }
    return minDistance;
}

void menu(int argc, char * argv[]){
    char opt = 'x';
    mode = 'i';
    if(argc > 1){
        if(argv[1][0] == '-'){
            mode = argv[1][1];
        }
    }
    if(mode == 'd'){
        xmax = atof(argv[2]);
        loadPoints(mode);
        draw();        
        destroy();
    }
    if(mode == 'n'){
        loadPoints(mode);        
        printf("%g\n", closestDistance());
        destroy();
    }
    while(opt != 's' && mode == 'i'){
        if(mode == 'i'){
            printf("--------------- MENU ---------------\n");
            printf("(l)oad points\n");
            printf("(q)uery\n");
            printf("(s)top\n");
            printf("---------------      ---------------\n");
            printf(">>> ");
        }
        scanf(" %c", &opt);
        if(opt == 's')
            destroy();
        else if(opt == 'q'){            
            printf("Closest distance: %g\n", closestDistance());
        }
        else if(opt == 'l')
            loadPoints(mode);
    }

}