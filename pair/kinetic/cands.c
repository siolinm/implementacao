#include"cands.h"

void updateMinimumCands(CandsNode * a, int dir){
    a->leftmost = minimumCands(a->left, a->right, dir);
    a->leftmost = minimumCands(a->leftmost, a, dir);
}

CandsNode * minimumCands(CandsNode * a, CandsNode * b, int dir){
    if(b == NULL)
        return a;
    else if(a == NULL)
        return b;
    
    return (getX(a->leftmost->key, dir) > getX(b->leftmost->key, dir) ? b->leftmost : a->leftmost);
}

CandsNode * createCandsNode(Item * key, int dir){
    CandsNode * new = malloc(sizeof(*new));
    new->left = new->right = NULL;
    new->parent = NULL;
    new->key = key;
    new->leftmost = new;
    key->cands[dir] = new;

    return new;
}

CandsNode * initCands(Item * p, int dir){
    CandsNode * new = malloc(sizeof(*new));
    new->left = new->right = NULL;
    new->parent = NULL;
    new->key = p;
    new->leftmost = new;    

    return new;
}

Point * queryCands(Item * q, int dir){
    CandsNode * p = NULL;
    p = q->cands[dir];    

    while(p && p != p->parent->parent)
        p = p->parent;
    
    if(p){
        p = p->parent;
        p->key->candsRoot[dir]->parent->parent = NULL;
        splayCands(q->cands[dir], dir);
        p->key->candsRoot[dir]->parent = q->cands[dir];
        q->cands[dir]->parent = p->key->candsRoot[dir];

        return p->key;
    }

    return NULL;
}

CandsNode * querySuccessorCands(CandsNode * root, Item * p, int order, int dir){
    double angle = 0;
    CandsNode *up, *y, *x;
    up = y = NULL;
    x = root->parent;

    if(order == UP){
        angle -= PI_3/2;
    }
    else if(order == DOWN){
        angle += PI_3/2;
    }
    
    while(x != NULL){
        y = x;

        if(checkLine(p, x->key, angle, dir) == -1){
            x = x->right;
        }
        else{
            up = x;
            x = x->left;
        }
    }

    if(y != NULL){
        root->parent->parent = NULL;
        splayCands(y, dir);
        root->parent = y;
        y->parent = root;
    }

    return up;
}

CandsNode * queryPredecessorCands(CandsNode * root, Item * p, int order, int dir){
    double angle = 0;
    CandsNode *low, *y, *x;
    low = y = NULL;
    x = root->parent;

    if(order == UP){
        angle -= PI_3/2;
    }
    else if(order == DOWN){
        angle += PI_3/2;
    }
    
    while(x != NULL){
        y = x;

        if(checkLine(p, x->key, angle, dir) <= 0){
            x = x->left;
        }
        else{
            low = x;
            x = x->right;
        }
    }

    if(y != NULL){
        root->parent->parent = NULL;
        splayCands(y, dir);
        root->parent = y;
        y->parent = root;
    }

    return low;
}

/* 
 * searchs for up/low(p) in the tree with root root and 
 * returns a subtree containing all nodes above/below
 * 
 */
CandsNode * extractCands(CandsNode * root, CandsNode *low, CandsNode * up, int dir){
    CandsNode *r;

    r =  root->parent;
    if(!r) return NULL;
    root->parent = NULL;
    r->parent = NULL;

    if(low != NULL){
        splayCands(low, dir);        
        root->parent = low;
        low->parent = root;        
        r = low->right;
        if(r) r->parent = NULL;
        low->right = NULL;

        updateMinimumCands(low, dir);
    }

    if(up != NULL){
        splayCands(up, dir);
        root->parent = up;
        up->parent = root;
        r = up->left;
        if(r) r->parent = NULL;
        up->left = NULL;

        updateMinimumCands(up, dir);
    }

    if(up != NULL && low != NULL){
        low->right = up;
        up->parent = low;
        root->parent = low;

        updateMinimumCands(low, dir);
    }

    return r;
}


/* attachs the joinRoot subtree to tree with root root */
void joinCands(CandsNode * root, CandsNode * joinRoot, int dir){
    CandsNode * aux = root->parent;
    if(joinRoot == NULL) return;

    root->parent = NULL;
    aux->parent = NULL;
    
    if(compareCands(aux->key, joinRoot->key, dir)){
        while(aux->left)
            aux = aux->left;
        splayCands(aux, dir);
        aux->left = joinRoot;
        joinRoot->parent = aux;
    }
    else{
        while(aux->right)
            aux = aux->right;
        splayCands(aux, dir);
        aux->right = joinRoot;
        joinRoot->parent = aux;
    }
    updateMinimumCands(aux, dir);
    root->parent = aux;
    aux->parent = root;
}

void rotateLeftCands(CandsNode * x, int dir){
    CandsNode * aux, *parent;
    
    parent = x->parent;
    aux = x->right;

    if(!aux) return;

    x->right = aux->left;
    if(aux->left)
        aux->left->parent = x;
    
    aux->left = x;
    x->parent = aux;
    aux->parent = parent;

    if(parent){
        if(parent->left == x)
            parent->left = aux;
        else
            parent->right = aux;
    }

    updateMinimumCands(x, dir);
    updateMinimumCands(aux, dir);
}

void rotateRightCands(CandsNode * x, int dir){
    CandsNode * aux, *parent;
    
    parent = x->parent;
    aux = x->left;
    if(!aux) return;

    x->left = aux->right;
    if(aux->right)
        aux->right->parent = x;
    
    aux->right = x;
    x->parent = aux;
    aux->parent = parent;

    if(parent){
        if(parent->left == x)
            parent->left = aux;
        else
            parent->right = aux;
    }

    updateMinimumCands(x, dir);
    updateMinimumCands(aux, dir);
}

void deleteCands(CandsNode * root, Item * key, int direction){
    CandsNode * parent;
    
    if(root->parent) root->parent->parent = NULL;
    root->parent = deleteCandsR(root->parent, key, &parent, direction);
    splayCands(parent, direction);
    root->parent = parent;
    parent->parent = root;
}

void swapCands(CandsNode *a, CandsNode * b, int dir){
    CandsNode * aux;
    aux = a->left;
    a->left = b->left;
    b->left = aux;
    
    aux = a->right;
    a->right = b->right;
    b->right = aux;

    aux = a->parent;
    if(aux){
        if(a == aux->left)
            aux->left = b;        
        else
            aux->right = b;
    }
    if(b->parent){
        if(b == b->parent->left)
            b->parent->left = a;        
        else
            b->parent->right = a;
    }
    a->parent = b->parent;
    b->parent = aux;

    updateMinimumCands(a, dir);
    updateMinimumCands(b, dir);
}

CandsNode * successorCands(CandsNode * root){
    while (root->left){
        root = root->left;
    }

    return root;    
}

CandsNode * deleteCandsR(CandsNode * root, Item * key, CandsNode **parent, int dir){
    CandsNode * aux;

    if(root->key == key){
        if(root->left && root->right){
            aux = successorCands(root->right);
            swapCands(root, aux, dir);
            aux->right = deleteCandsR(aux->right, key, parent, dir);

            root = aux;
        }
        else{
            *parent = root->parent;
            aux = (root->left ? root->left : root->right);
            
            if(aux) aux->parent = aux->parent->parent;
            
            if(root->parent){
                if(root->parent->left == root)
                    root->parent->left = aux;
                else
                    root->parent->right = aux;
            }

            root->key->cands[dir] = NULL;
            free(root);

            root = aux;
        }
    }
    else if(compareCands(root->key, key, dir)){
        root->left = deleteCandsR(root->left, key, parent, dir);        
        if(root->left)
            root->left->parent = root;
    }
    else{
        root->right = deleteCandsR(root->right, key, parent, dir);
        if(root->right)
            root->right->parent = root;
    }

    if(root){
        CandsNode * leftmost;
        
        leftmost = minimumCands(root->left, root->right, dir);
        leftmost = minimumCands(leftmost, root, dir);
        
        root->leftmost = leftmost;
    }

    return root;
}

void insertCands(CandsNode * root, Item * key, int direction){
    CandsNode * new = createCandsNode(key, direction);    
    if(root->parent) root->parent->parent = NULL;
    root->parent = insertCandsR(root->parent, new, direction);

    splayCands(new, direction);
    root->parent = new;
    new->parent = root;
}

CandsNode * insertCandsR(CandsNode * root, CandsNode * no, int dir){
    CandsNode * leftmost;
    if(!root)
        return no;

    if(compareCands(root->key, no->key, dir)){
        root->left = insertCandsR(root->left, no, dir);
        root->left->parent = root;
    }
    else{
        root->right = insertCandsR(root->right, no, dir);
        root->right->parent = root;
    }

    
    leftmost = minimumCands(root->left, root->right, dir);
    leftmost = minimumCands(leftmost, root, dir);
    
    root->leftmost = leftmost;

    return root;
}

void splayCands(CandsNode * x, int dir){
    while(x && x->parent){
        /*
            l or r case
        */
        if(!x->parent->parent){
            if(x->parent->left == x)
                rotateRightCands(x->parent, dir);
            else
                rotateLeftCands(x->parent, dir);
        }
        else{
            if(x->parent->left == x){
                /* rr case*/
                if(x->parent->parent->left == x->parent){
                    rotateRightCands(x->parent->parent, dir);
                    rotateRightCands(x->parent, dir);
                }
                else{
                    /* rl case */
                    rotateRightCands(x->parent, dir);
                    rotateLeftCands(x->parent, dir);
                }
            }
            else{
                /* lr case */
                if(x->parent->parent->left == x->parent){
                    rotateLeftCands(x->parent, dir);
                    rotateRightCands(x->parent, dir);
                }
                else{
                    /* ll case */
                    rotateLeftCands(x->parent->parent, dir);
                    rotateLeftCands(x->parent, dir);
                }
            }
        }
    }
}

int compareCands(Item * a, Item * b, int dir){
    if(getY(a, dir) > getY(b, dir))
        return 1;
    return 0;
}

void freeAllCands(CandsNode * r){
    if(r != NULL){
        freeAllCands(r->left);
        freeAllCands(r->right);
        free(r);
    }    
}

/*
void print(char * prefix, int size, CandsNode * r, int b){
	int i;
    char * new;
    if(prefix == NULL){
        prefix = malloc(sizeof(*prefix));
        prefix[0] = '\0';
    }
    if(r != NULL)
    {
        for(i = 0; prefix[i] != '\0'; i++)
            printf("%c", prefix[i]);

        if(b) 
            printf("├──"); 
        else 
            printf("└──" );
        printf("(%g, %g)", r->key->x, r->key->y);
        if(r->parent){
            printf("'s parent: (%g, %g)", r->parent->key->x, r->parent->key->y);
        }
		printf("\n");
        new = malloc((size + 4)*sizeof(*new));
        for(i = 0; root = NULL;i < size; i++)
            new[i] = prefix[i];
        if(b)
            new[size - 1] = '|';
        else
            new[size - 1] = ' ';
        for(i = size; i < size + 4; i++)
            new[i] = ' ';        
        new[size + 3] = '\0';
		print(new, size + 4, r->left, 1);
        print(new, size + 4, r->right, 0);
        
    }
    if(!b)
        free(prefix);
}
*/