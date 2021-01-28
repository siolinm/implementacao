#include"splay_tree.h"
#include"debug.h"

void insertS(void * root, Point * a, int type, int dir){
    void * new;

    new = createNodeS(a, type, dir);    
        
    insertSR(detach(root, type, dir), new, type, dir);
    splay(new, type, dir);
    attach(root, new, type, dir);
}

void deleteS(void * root, Point * a, int type, int dir){
    void * parent;    
        
    deleteSR(detach(root, type, dir), a, &parent, type, dir);
    splay(parent, type, dir);
    attach(root, parent, type, dir);
}

void splay(void * x, int type, int dir){
    void * parent, *grandp;
    
    while(x && getParentS(x, type)){
        /*
            l or r case
        */
        parent = getParentS(x, type);
        grandp = getParentS(parent, type);
        if(!grandp){
            if(getLeftS(parent, type) == x)
                rotateRightS(parent, type, dir);
            else
                rotateLeftS(parent, type, dir);
        }
        else{
            if(getLeftS(parent, type) == x){
                /* rr case*/
                if(getLeftS(grandp, type) == parent){
                    rotateRightS(grandp, type, dir);
                    rotateRightS(parent, type, dir);
                }
                else{
                    /* rl case */
                    rotateRightS(parent, type, dir);
                    rotateLeftS(parent, type, dir);
                }
            }
            else{
                /* lr case */
                if(getLeftS(grandp, type) == parent){
                    rotateLeftS(parent, type, dir);
                    rotateRightS(parent, type, dir);
                }
                else{
                    /* ll case */
                    rotateLeftS(grandp, type, dir);
                    rotateLeftS(parent, type, dir);
                }
            }
        }
    }
}

void * splitL(void *root, int type, int dir){
    void * left;
    splay(root, type, dir);

    left = getLeftS(root, type);

    if(left){
        setLeftS(root, NULL, type);
        setParentS(left, NULL, type);
    }

    return left;
}

void * splitR(void * root, int type, int dir){
    void * right;
    splay(root, type, dir);

    right = getRightS(root, type);

    if(right){
        setRightS(root, NULL, type);
        setParentS(right, NULL, type);
    }
    
    return right;
}

/* S < T */
void * joinS(void * rootS, void * rootT, int type, int dir){
    void * aux = rootS;

    if(aux == NULL)
        return rootT;
    
    while(getRightS(aux, type) != NULL){
        aux = getRightS(aux, type);
    }

    splay(aux, type, dir);

    setRightS(aux, rootT, type);
    setParentS(rootT, aux, type);
    
    if(type == CANDS_TREE)
        updateLeftmost(aux, dir);

    return aux;
}

void * successorS(void * root, Item * p, int type, int dir, int order){    
    void *suc, *y, *x;
    int mirror = 0;
    int orientation;
    suc = y = NULL;
    x = getParentS(root, type);

    orientation = dir;
    if(type == CANDS_TREE && order == UP){
        mirror = 1;
    }
    if(dir == HORIZONTAL){
        if(order == UP)
            orientation = DOWN;
        else if(order == DOWN)
            orientation = UP;   
    }
    else if(dir == UP){
        /* TODO */
        if(order == UP)
            orientation = HORIZONTAL;
        else if(order == DOWN)
            orientation = 11111;
    }
    else{ /* dir = DOWN */
        if(order == UP)
            orientation = 11111;
        else if(order == DOWN)
            orientation = 11111;
    }
    
    while(x != NULL){
        y = x;
        /* rounding errors */
        if(getX(getKeyS(x, type), orientation) < getX(p, orientation)) {
            if(!mirror)
                x = getRightS(x, type);
            else
                x = getLeftS(x, type);
        }
        else{
            suc = x;
            if(!mirror)
                x = getLeftS(x, type);            
            else
                x = getRightS(x, type);
        }
    }

    if(y != NULL){
        detach(root, type, dir);
        splay(y, type, dir);
        attach(root, y, type, dir);        
    }

    return suc;
}

void * predecessorS(void * root, Item * p, int type, int dir, int order){    
    void *pred, *y, *x;
    int orientation;
    int mirror = 0;
    pred = y = NULL;
    x = getParentS(root, type);
    
    orientation = dir;
    if(dir == HORIZONTAL){
        if(order == UP)
            orientation = DOWN;
        else if (order == DOWN)
            orientation = UP;
        
        if(type == CANDS_TREE && order == UP){
            mirror = 1;
        }
    }
    else if(dir == UP){

    }
    else{ /* dir = DOWN */

    }

    while(x != NULL){
        y = x;
        /* rounding errors */
        if(getX(getKeyS(x, type), orientation) >= getX(p, orientation)) {
            if(!mirror)
                x = getLeftS(x, type);            
            else
                x = getRightS(x, type);            
        }
        else{
            pred = x;
            if(!mirror)
                x = getRightS(x, type);            
            else
                x = getLeftS(x, type);
        }
    }

    if(y != NULL){
        detach(root, type, dir);
        splay(y, type, dir);
        attach(root, y, type, dir);      
    }

    return pred;
}

Point * ownerS(void * root, int type, int dir){
    void * aux = root;
    
    while(aux && aux != getParentS(getParentS(aux, type), type)){
        aux = getParentS(aux, type);
    }

    if(aux){
        aux = getParentS(aux, type);
        detach(aux, type, dir);
        splay(root, type, dir);
        attach(aux, root, type, dir);

        return getKeyS(aux, type);
    }

    return NULL;
}

/* ---------------------------------------------- */

void updateLeftmost(void * x, int dir){
    void * a, * b, *c, * left, * right;
    a = b = c = NULL;
    left = getLeftS(x, CANDS_TREE);
    right = getRightS(x, CANDS_TREE);
    if(left)
        a = getLeftmostS(left, CANDS_TREE);
    if(right)
        b = getLeftmostS(right, CANDS_TREE);
    
    if(a && b){
        if(getX(getKeyS(a, CANDS_TREE), dir) < 
        getX(getKeyS(b, CANDS_TREE), dir))
            c = a;
        else
            c = b;
    }
    else if(a){
        c = a;
    }
    else if(b){
        c = b;
    }

    setLeftmostS(x, x, CANDS_TREE);
    if(c && getX(getKeyS(c, CANDS_TREE), dir) < 
        getX(getKeyS(x, CANDS_TREE), dir)){
        setLeftmostS(x, c, CANDS_TREE);
    }    
}

void rotateLeftS(void * x, int type, int dir){
    void * aux, *parent;
    
    parent = getParentS(x, type);
    aux = getRightS(x, type);

    if(!aux) return;

    setRightS(x, getLeftS(aux, type), type);    
    if(getLeftS(aux, type))
        setParentS(getLeftS(aux, type), x, type);
    
    setLeftS(aux, x, type);
    setParentS(x, aux, type);
    setParentS(aux, parent, type);

    if(parent){
        if(getLeftS(parent, type) == x)
            setLeftS(parent, aux, type);
        else
            setRightS(parent, aux, type);
    }

    if(type == CANDS_TREE){
        updateLeftmost(x, dir);
        updateLeftmost(aux, dir);
    }
}

void rotateRightS(void * x, int type, int dir){
    void * aux, *parent;
    
    parent = getParentS(x, type);
    aux = getLeftS(x, type);

    if(!aux) return;

    setLeftS(x, getRightS(aux, type), type);    
    if(getRightS(aux, type))
        setParentS(getRightS(aux, type), x, type);
    
    setRightS(aux, x, type);
    setParentS(x, aux, type);
    setParentS(aux, parent, type);

    if(parent){
        if(getLeftS(parent, type) == x)
            setLeftS(parent, aux, type);
        else
            setRightS(parent, aux, type);
    }

    if(type == CANDS_TREE){
        updateLeftmost(x, dir);
        updateLeftmost(aux, dir);
    }
}

void initS(Point * p, int type, int dir){
    void * new;
    if(type == CANDS_TREE){
        new = (void *)malloc(sizeof(CandsNode));
        setLeftmostS(new, new, type);
    }
    else{
        new = (void *)malloc(sizeof(HitsNode));
    }

    setLeftS(new, NULL, type);
    setRightS(new, NULL, type);
    setParentS(new, NULL, type);
    setKeyS(new, p, type);

    if(type == CANDS_TREE){
        p->candsRoot[dir] = new;
    }
    else if(type == HITS_UP_TREE){
        p->hitsUpRoot[dir] = new;
    } 
    else if(type == HITS_LOW_TREE){
        p->hitsLowRoot[dir] = new;
    } 

}

void * createNodeS(Point * key, int type, int dir){
    void * new;
    if(type == CANDS_TREE){
        new = (void *)malloc(sizeof(CandsNode));
        setLeftmostS(new, new, type);
    }
    else{
        new = (void *)malloc(sizeof(HitsNode));
    }
    setLeftS(new, NULL, type);
    setRightS(new, NULL, type);
    setParentS(new, NULL, type);
    setKeyS(new, key, type);

    if(type == CANDS_TREE){
        key->cands[dir] = (CandsNode *)new;
    }
    else if(type == HITS_UP_TREE){
        key->hitsUp[dir] = (HitsNode *)new;
    }
    else if(type == HITS_LOW_TREE){
        key->hitsLow[dir] = (HitsNode *)new;
    }

    return new;
}

void * insertSR(void * root, void * node, int type, int dir){    
    void * sub;
    if(!root)
        return node;    

    if(compareS(getKeyS(root, type), getKeyS(node, type), type, dir)){
        sub = insertSR(getLeftS(root, type), node, type, dir);
        setLeftS(root, sub, type);
        setParentS(sub, root, type);        
    }
    else{
        sub = insertSR(getRightS(root, type), node, type, dir);
        setRightS(root, sub, type);
        setParentS(sub, root, type);
    }

    if(type == CANDS_TREE)
        updateLeftmost(root, dir);

    return root;
}

void * extractS(void * root, void * low, void * up, int type, int dir){
    void * r = NULL;
    db(
        printf("extractS:: before extract\n");
        printS(root, type);
    );
    r = detach(root, type, dir);
    if(low != NULL){
        splay(low, type, dir);

        r = splitR(low, type, dir);
        
        if(type == CANDS_TREE)
            updateLeftmost(low, dir);
        if(!up)
            attach(root, low, type, dir);
    }

    if(up != NULL){
        splay(up, type, dir);

        r = splitL(up, type, dir);

        if(type == CANDS_TREE)
            updateLeftmost(up, dir);
        attach(root, up, type, dir);
    }

    if(up != NULL && low != NULL){
        detach(root, type, dir);
        attach(root, joinS(low, up, type, dir), type, dir);

        if(type == CANDS_TREE)
            updateLeftmost(low, dir);
        
    }

    db(
        printf("extractS:: after extract\n");
        printS(root, type);
    );

    return r;
}

void * deleteSR(void * root, Point * a, void **parent, int type, int dir){
    void * aux = root;

    if(getKeyS(root, type) == a){
        if(getLeftS(root, type) && getRightS(root, type)){
            aux = getRightS(root, type);
            while(getRightS(aux, type) != NULL){
                aux = getRightS(aux, type);
            }
            swapS(root, aux, type, dir);
            setRightS(aux, deleteSR(getRightS(aux, type), a, 
            parent, type, dir), type);

            root = aux;
        }
        else{
            *parent = getParentS(root, type);
            aux = (getLeftS(root, type) ? getLeftS(root, type) 
            : getRightS(root, type));
            
            if(aux) setParentS(aux, getParentS(getParentS(aux, type), 
            type), type);
            
            if(getParentS(root, type)){
                if(getLeftS(getParentS(root, type), type) == root)
                    setLeftS(getParentS(root, type), aux, type);
                else
                    setRightS(getParentS(root, type), aux, type);
            }

            if(type == CANDS_TREE)
                a->cands[dir] = NULL;
            else if(type == HITS_UP_TREE)
                a->hitsUp[dir] = NULL;
            else if(type == HITS_LOW_TREE)
                a->hitsLow[dir] = NULL;
            
            free(root);

            root = aux;
        }
    }
    else if(compareS(getKeyS(root, type), a, type, dir)){
        setLeftS(root, deleteSR(getLeftS(root, type), a, 
        parent, type, dir), type);
        if(getLeftS(root, type))
            setParentS(getLeftS(root, type), root, type);
    }
    else{
        setRightS(root, deleteSR(getRightS(root, type), a, 
        parent, type, dir), type);
        if(getRightS(root, type))
            setParentS(getRightS(root, type), root, type);
    }

    if(root && type == CANDS_TREE){
        updateLeftmost(root, dir);
    }

    return root;
}

int compareS(Point * a, Point * b, int type, int dir){
    if(type == CANDS_TREE){
        return getY(a, dir) >= getY(b, dir);
    }
    
    return getX(a, dir) >= getX(b, dir);    
}

void swapS(void * roota, void * rootb, int type, int dir){
    void * aux;
    aux = getLeftS(roota, type);
    setLeftS(roota, getLeftS(rootb, type), type);
    setLeftS(rootb, aux, type);
        
    aux = getRightS(roota, type);    
    setRightS(roota, getRightS(rootb, type), type);    
    setRightS(rootb, aux, type);
    
    aux = getParentS(roota, type);
    if(aux){
        if(roota == getLeftS(aux, type))            
            setLeftS(aux, rootb, type);
        else            
            setRightS(aux, rootb, type);
    }
    if(getParentS(rootb, type)){        
        if(rootb == getLeftS(getParentS(rootb, type), type))            
            setLeftS(getParentS(rootb, type), roota, type);         
        else
            setRightS(getParentS(rootb, type), roota, type);            
    }
    setParentS(roota, getParentS(rootb, type), type);    
    setParentS(rootb, aux, type);

    if(type == CANDS_TREE){
        updateLeftmost(roota, dir);
        updateLeftmost(rootb, dir);
    }
}

void * detach(void * root, int type, int dir){
    void * aux;

    if(!root) return root;

    aux = getParentS(root, type);
    if(aux)
        setParentS(aux, NULL, type);
    setParentS(root, NULL, type);
    return aux;
}

void attach(void * roota, void * rootb, int type, int dir){
    setParentS(roota, rootb, type);    
    if(rootb) setParentS(rootb, roota, type);
}

void freeAllS(void * root, int type){
    Point * p;
    int i;
    if(root){
        freeAllS(getLeftS(root, type), type);
        freeAllS(getRightS(root, type), type);
        p = getKeyS(root, type);
        if(p != NULL){
            if(type == CANDS_TREE){
                for(i = 0; i < 3; i++)
                    p->cands[i] = NULL;
            }
            else if(type == HITS_UP_TREE){
                for(i = 0; i < 3; i++)
                    p->hitsUp[i] = NULL;
            }
            else{
                for(i = 0; i < 3; i++)
                    p->hitsLow[i] = NULL;
            }            
        }
        free(root);
    }
}

void setLeftS(void * x, void * y, int type){
    if(type == CANDS_TREE){
        ((CandsNode * )x)->left = (CandsNode *)y;
    }
    else{
        ((HitsNode * )x)->left = (HitsNode *)y;
    }
}

void setRightS(void * x, void * y, int type){
    if(type == CANDS_TREE){
        ((CandsNode * )x)->right = (CandsNode *)y;
    }
    else{
        ((HitsNode * )x)->right = (HitsNode *)y;
    }
}

void setParentS(void * x, void * y, int type){
    if(type == CANDS_TREE){
        ((CandsNode * )x)->parent = (CandsNode *)y;
    }
    else{
        ((HitsNode * )x)->parent = (HitsNode *)y;
    }
}

void setKeyS(void * x, Point * y, int type){
    if(type == CANDS_TREE){
        ((CandsNode * )x)->key = y;
    }
    else{
        ((HitsNode * )x)->key = y;
    }
}

void setLeftmostS(void * x, void * y, int type){    
    ((CandsNode * )x)->leftmost = (CandsNode *)y;
}

void * getLeftS(void * x, int type){
    if(type == CANDS_TREE){
        return (void *)((CandsNode * )x)->left;
    }
    else{
        return (void *)((HitsNode * )x)->left;
    }
}

void * getRightS(void * x, int type){
    if(type == CANDS_TREE){
        return (void *)((CandsNode * )x)->right;
    }
    else{
        return (void *)((HitsNode * )x)->right;
    }
}

void * getParentS(void * x, int type){
    if(type == CANDS_TREE){
        return (void *)((CandsNode * )x)->parent;
    }
    else{
        return (void *)((HitsNode * )x)->parent;
    }
}

Point * getKeyS(void * x, int type){
    if(type == CANDS_TREE){
        return ((CandsNode *)x)->key;
    }

    return ((HitsNode *)x)->key;
}

void * getLeftmostS(void * x, int type){
    return (void *)((CandsNode * )x)->leftmost;
}

void printS(void * root, int type){
    printSR(getParentS(root, type), NULL, type, 1, 0);
}

void printSR(void * root, char * prefix, int type, int size, int b){
    int i;
    char * newprefix;
    Point * key;
    if(prefix == NULL){
        prefix = malloc(sizeof(*prefix));
        prefix[0] = '\0';
    }
    if(root != NULL)
    {
        for(i = 0; prefix[i] != '\0'; i++)
            printf("%c", prefix[i]);

        if(b) 
            printf("├──"); 
        else 
            printf("└──");
        key = getKeyS(root, type);
        printf("%c: (%g, %g) + t*(%g, %g)", key->name, key->x0.x, key->x0.y, key->speed.x, key->speed.y);

        if(type == CANDS_TREE){
            printf(", leftmost: %c", ((CandsNode *)getLeftmostS(root, type))->key->name);
        }
        printf("\n");

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
		printSR(getLeftS(root, type), newprefix, type, size + 4, 1);
        printSR(getRightS(root, type), newprefix, type, size + 4, 0);        
    }
    else{
        printf("%s", prefix);
        if(b) 
            printf("├── NULL\n"); 
        else 
            printf("└── NULL\n");
    }
    if(!b)
        free(prefix);
}
