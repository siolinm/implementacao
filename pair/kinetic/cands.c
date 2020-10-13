#include"cands.h"

#warning ajustar todas as funcoes de cands e Hits por conta da cabeca

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

CandsNode * createCandsNode(Item * key){
    CandsNode * new = malloc(sizeof(*new));
    new->left = new->right = NULL;
    new->parent = NULL;
    new->key = key;
    new->leftmost = new;
    return new;
}

CandsNode * initCands(Item * p){
    return createCandsNode(p);
}

Point * queryCands(Item * q, int dir){
    CandsNode * p = NULL;
    p = q->cands[dir];

    while(p != NULL && p->parent != p->parent->parent)
        p = p->parent->parent;

    if(p){
        p->key->candsRoot[dir] = q->cands[dir];
        splayCands(q->cands[dir]);
        return p->key;
    }

    return NULL;
}

CandsNode * querySuccessorCands(CandsNode * root, Item * p, int order, int dir){
    double angle;
    CandsNode *up, *y, *x;
    up = y = NULL;
    x = root->parent;
    
    if(dir == HORIZONTAL){
        angle = 0;
    }
    else if(dir == UP){
        angle = PI_3;
    }
    else if(dir == DOWN){
        angle = -PI_3;
    }

    if(order == UP){
        angle -= PI_3/2;
    }
    else if(order == DOWN){
        angle += PI_3/2;
    }
    
    while(x != NULL){
        y = x;

        if(checkLine(p, x->key, angle) == -1){
            x = x->right;
        }
        else{
            up = x;
            x = x->left;
        }
    }

    if(y != NULL){
        root->parent->parent = NULL;
        splayCands(y);
        root->parent = y;
    }

    return up;
}

CandsNode * queryPredecessorCands(CandsNode * root, Item * p, int order, int dir){
    double angle;
    CandsNode *low, *y, *x;
    low = y = NULL;
    x = root->parent;    
    if(dir == HORIZONTAL){
        angle = 0;
    }
    else if(dir == UP){
        angle = PI_3;
    }
    else if(dir == DOWN){
        angle = -PI_3;
    }

    if(order == UP){
        angle -= PI_3/2;
    }
    else if(order == DOWN){
        angle += PI_3/2;
    }
    
    while(x != NULL){
        y = x;

        if(checkLine(p, x->key, angle) <= 0){
            x = x->left;
        }
        else{
            low = x;
            x = x->right;
        }
    }

    if(y != NULL){
        root->parent->parent = NULL;
        splayCands(y);
        root->parent = y;
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
    root->parent = NULL;
    r->parent = NULL;
    if(low != NULL){
        splayCands(low);        
        root->parent = low;
        r = low->right;
        r->parent = NULL;
        updateMinimumCands(low, dir);
    }

    if(up != NULL){
        splayCands(up);
        root->parent = up;
        r = up->left;
        r->parent = NULL;

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

}

#warning adjust leftmost on rotation
void rotateLeftCands(CandsNode * x){
    CandsNode * aux, *parent;
    
    parent = x->parent;
    aux = x->right;
    if(!aux)
        return;

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

}

void rotateRightCands(CandsNode * x){
    CandsNode * aux, *parent;
    
    parent = x->parent;
    aux = x->left;
    if(!aux)
        return;

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
}

void deleteCands(CandsNode * root, Item * key, int direction){

}

CandsNode * deleteCandsR(CandsNode * root, Item * key, int direction){

}

void insertCands(CandsNode * root, Item * key, int direction){
    CandsNode * new = createCandsNode(key);
    CandsNode * parent = root, *x;
    
    root->parent = insertCandR(root->parent, new, direction);
    root->parent->parent = NULL;
    splayCands(new);
    root->parent = new;
    new->parent = root;
}

CandsNode * insertCandR(CandsNode * root, CandsNode * no, int dir){
    if(!root)
        return no;

    if(compare(root->key, no->key, dir)){
        root->left = insertCandR(root->left, no, dir);
        root->left->parent = root;
    }
    else{
        root->right = insertCandR(root->right, no, dir);
        root->right->parent = root;
    }

    CandsNode * leftmost;
    
    leftmost = minimumCands(root->left->leftmost, root->right->leftmost, dir);
    leftmost = minimumCands(leftmost, root, dir);
    
    root->leftmost = leftmost;

    return root;
}

#warning refazer essa funcao
void splayCands(CandsNode * x){
    while(x && x->parent && x->parent != x->parent->parent){
        /*
            l or r case
        */
        if(!x->parent->parent){
            if(x->parent->left == x)
                rotateRightCands(x->parent);
            else
                rotateLeftCands(x->parent);
        }
        else{
            if(x->parent->left == x){
                /* rr case*/
                if(x->parent->parent->left == x->parent){
                    rotateRightCands(x->parent->parent);
                    rotateRightCands(x->parent);
                }
                else{
                    /* rl case */
                    rotateRightCands(x->parent);
                    rotateLeftCands(x->parent);
                }
            }
            else{
                /* lr case */
                if(x->parent->parent->left == x->parent){
                    rotateLeftCands(x->parent);
                    rotateRightCands(x->parent);
                }
                else{
                    /* ll case */
                    rotateLeftCands(x->parent->parent);
                    rotateLeftCands(x->parent);
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