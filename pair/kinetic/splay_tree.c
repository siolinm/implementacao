#include"splay_tree.h"

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
    while(x && getParentS(x, type)){
        /*
            l or r case
        */
        if(!getParentS(getParentS(x, type), type)){
            if(getLeftS(getParentS(x, type), type) == x)
                rotateRightS(getParentS(x, type), type, dir);
            else
                rotateLeftS(getParentS(x, type), type, dir);
        }
        else{
            if(getLeftS(getParentS(x, type), type) == x){
                /* rr case*/
                if(getLeftS(getParentS(getParentS(x, type), type), type) 
                == getParentS(x, type)){
                    rotateRightS(getParentS(getParentS(x, type), type), type, 
                    dir);
                    rotateRightS(getParentS(x, type), type, dir);
                }
                else{
                    /* rl case */
                    rotateRightS(getParentS(x, type), type, dir);
                    rotateLeftS(getParentS(x, type), type, dir);
                }
            }
            else{
                /* lr case */
                if(getLeftS(getParentS(getParentS(x, type), type), type) 
                == getParentS(x, type)){
                    rotateLeftS(getParentS(x, type), type, dir);
                    rotateRightS(getParentS(x, type), type, dir);
                }
                else{
                    /* ll case */
                    rotateLeftS(getParentS(getParentS(x, type), type), type, 
                    dir);
                    rotateLeftS(getParentS(x, type), type, dir);
                }
            }
        }
    }
}

void * splitL(void *root, int type, int dir){
    splay(root, type, dir);
    return detach(getLeftS(root, type), type, dir);
}

void * splitR(void * root, int type, int dir){
    splay(root, type, dir);
    return detach(getRightS(root, type), type, dir);
}

/* S < T */
void * joinS(void * rootS, void * rootT, int type, int dir){
    void * aux = rootS;
    
    while(getLeftS(aux, type) != NULL){
        aux = getLeftS(aux, type);
    }

    splay(aux, type, dir);

    setRightS(aux, rootT, type);
    setParentS(rootT, aux, type);

    return aux;
}

void * successorS(void * root, Item * p, int type, int dir, int order){
    double angle = 0;
    void *up, *y, *x;
    up = y = NULL;
    x = getParentS(root, type);

    if(order == UP){
        angle -= PI_3/2;
    }
    else if(order == DOWN){
        angle += PI_3/2;
    }
    
    while(x != NULL){
        y = x;

        if(checkLine(p, getKeyS(x, type), angle, dir) == -1){
            x = getRightS(x, type);
        }
        else{
            up = x;
            x = getLeftS(x, type);
        }
    }

    if(y != NULL){
        detach(root, type, dir);
        splay(y, type, dir);
        attach(root, y, type, dir);        
    }

    return up;
}

void * predecessorS(void * root, Item * p, int type, int dir, int order){
    double angle = 0;
    void *low, *y, *x;
    low = y = NULL;
    x = getParentS(root, type);

    if(order == UP){
        angle -= PI_3/2;
    }
    else if(order == DOWN){
        angle += PI_3/2;
    }
    
    while(x != NULL){
        y = x;

        if(checkLine(p, getKeyS(x, type), angle, dir) <= 0){
            x = getLeftS(x, type);
        }
        else{
            low = x;            
            x = getRightS(x, type);
        }
    }

    if(y != NULL){
        detach(root, type, dir);
        splay(y, type, dir);
        attach(root, y, type, dir);      
    }

    return low;
}

Point * ownerS(void * root, int type, int dir){
    void * aux = root;
    
    while(aux && aux != getParentS(getParentS(aux, type), type)){
        aux = getParentS(aux, type);
    }

    if(aux){
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
    if(!root)
        return node;

    if(compareS(root, node, type, dir)){
        setLeftS(root, insertSR(getLeftS(root, type), 
        node, type, dir), type);
        setParentS(getLeftS(root, type), root, type);        
    }
    else{
        setLeftS(root, insertSR(getLeftS(root, type), 
        node, type, dir), type);
        setParentS(getLeftS(root, type), root, type);
    }

    if(type == CANDS_TREE)
        updateLeftmost(root, dir);

    return root;
}

void * extractS(void * root, void * low, void * up, int type, int dir){
    void * r = NULL;

    r = detach(root, type, dir);
    if(low != NULL){
        splay(low, type, dir);
        attach(root, low, type, dir);

        r = splitR(low, type, dir);
        
        if(type == CANDS_TREE)
            updateLeftmost(low, dir);
    }

    if(up != NULL){
        splay(up, type, dir);
        attach(root, up, type, dir);

        r = splitL(up, type, dir);

        if(type == CANDS_TREE)
            updateLeftmost(up, dir);
    }

    if(up != NULL && low != NULL){
        attach(root, joinS(low, up, type, dir), type, dir);

        if(type == CANDS_TREE)
            updateLeftmost(low, dir);
        
    }

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
        return getY(a, dir) < getY(b, dir);
    }
    
    return getX(a, dir) < getX(b, dir);    
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
    void * aux = getParentS(root, type);
    if(aux)
        setParentS(aux, NULL, type);
    setParentS(root, NULL, type);
    return aux;
}

void attach(void * roota, void * rootb, int type, int dir){
    setParentS(roota, rootb, type);
    setParentS(rootb, roota, type);
}

void freeAllS(void * root, int type){
    if(root){
        freeAllS(getLeftS(root, type), type);
        freeAllS(getRightS(root, type), type);
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