#include"cands.h"

#define minimum(a, b, dir) (getX(a, dir) > getX(b, dir) ? b : a)

HitsNode * createHitsNode(Item * key){
    HitsNode * new = malloc(sizeof(*new));
    new->left = new->right = NULL;
    new->parent = NULL;
    new->key = key;
    return new;
}

HitsNode * initHits(Item * p){
    return createHitsNode(p);
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

Item * queryHitsLow(Item * q, int dir){
    HitsNode * p = NULL;
    p = q->hitsLow[dir];

    while(p != NULL && p->parent != p->parent->parent)
        p = p->parent->parent;

    if(p) return p->key;

    return NULL;
}

Item * queryHitsUp(Item * q, int dir){
    HitsNode * p = NULL;
    p = q->hitsUp[dir];

    while(p != NULL && p->parent != p->parent->parent)
        p = p->parent->parent;

    if(p) return p->key;

    return NULL;
}

/* attachs the joinRoot subtree to tree with root root */
HitsNode * joinHits(HitsNode * root, HitsNode * joinRoot, int dir){

}

/* if left = 1 searchs for the leftmost point t to the right of p 
 * in the tree with root root and returns a subtree 
 * containing all nodes to the left of t
 * 
 * if left = 0 searchs for the rightmost point v that doesn't hits
 * Dom(p) and returns a subtree containing all nodes to the right of v
 */
HitsNode * cutHits(HitsNode * root, Item * p, int left, int dir){

}

#warning adjust leftmost on rotation
void rotateLeftHits(HitsNode * x){
    HitsNode * aux, *parent;
    
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

void rotateRightHits(HitsNode * x){
    HitsNode * aux, *parent;
    
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

void deleteHits(HitsNode * root, Item * key, int direction){

}

HitsNode * deleteHitsR(HitsNode * root, Item * key, int direction){

}

void insertHits(HitsNode * root, Item * key, int direction){
    HitsNode * new = createHitsNode(key);
    HitsNode * parent = root, *x;
    
    root->parent = insertCandR(root, new, direction);
    root->parent->parent = NULL;
    splayHits(new);
    root->parent = new;
    new->parent = root;
}

HitsNode * insertHitsR(HitsNode * root, HitsNode * no, int dir){
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

    return root;
}

void splayHits(HitsNode * x){
    while(x && x->parent){
        /*
            l or r case
        */
        if(!x->parent->parent){
            if(x->parent->left == x)
                rotateRightHits(x->parent);
            else
                rotateLeftHits(x->parent);
        }
        else{
            if(x->parent->left == x){
                /* rr case*/
                if(x->parent->parent->left == x->parent){
                    rotateRightHits(x->parent->parent);
                    rotateRightHits(x->parent);
                }
                else{
                    /* rl case */
                    rotateRightHits(x->parent);
                    rotateLeftHits(x->parent);
                }
            }
            else{
                /* lr case */
                if(x->parent->parent->left == x->parent){
                    rotateLeftHits(x->parent);
                    rotateRightHits(x->parent);
                }
                else{
                    /* ll case */
                    rotateLeftHits(x->parent->parent);
                    rotateLeftHits(x->parent);
                }
            }
        }
    }
}

int compareHits(Item * a, Item * b, int dir){
    if(getX(a, dir) < getX(b, dir))
        return 1;
    return 0;
}

void freeAllHits(HitsNode * r){
    if(r != NULL){
        freeAllHits(r->left);
        freeAllHits(r->right);
        free(r);
    }    
}

/*
void print(char * prefix, int size, HitsNode * r, int b){
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