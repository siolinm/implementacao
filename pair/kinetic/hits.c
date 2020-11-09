#include"hits.h"

HitsNode * createHitsNode(Item * key, int dir, int up){
    HitsNode * new = malloc(sizeof(*new));
    new->left = new->right = NULL;
    new->parent = NULL;
    new->key = key;

    if(up)
        key->hitsUp[dir] = new;
    else
        key->hitsLow[dir] = new;

    return new;
}

HitsNode * initHits(Item * p, int dir){
    HitsNode * new = malloc(sizeof(*new));
    new->left = new->right = NULL;
    new->parent = NULL;
    new->key = p;

    return new;
}

HitsNode * querySuccessorHits(HitsNode * root, Item * p, int dir){
    return NULL;
}

HitsNode * queryPredecessorHits(HitsNode * root, Item * p, int dir){
    return NULL;
}

Item * queryHitsLow(Item * q, int dir){
    HitsNode * p = NULL;
    p = q->hitsLow[dir];    

    while(p && p != p->parent->parent)
        p = p->parent;
    
    if(p){
        p = p->parent;
        p->key->hitsLowRoot[dir]->parent->parent = NULL;
        splayHits(q->hitsLow[dir]);
        p->key->hitsLowRoot[dir]->parent = q->hitsLow[dir];
        q->hitsLow[dir]->parent = p->key->hitsLowRoot[dir];

        return p->key;
    }

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

HitsNode * successorHits(HitsNode * root){
    while (root->left){
        root = root->left;
    }

    return root;
}

void swapHits(HitsNode *a, HitsNode * b, int dir){
    HitsNode * aux;
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
}

void deleteHits(HitsNode * root, Item * key, int dir, int up){
    HitsNode * parent;
    
    if(root->parent) root->parent->parent = NULL;
    root->parent = deleteHitsR(root->parent, key, &parent, dir, up);
    splayHits(parent);
    root->parent = parent;
    parent->parent = root;
}

HitsNode * deleteHitsR(HitsNode * root, Item * key, HitsNode **parent, int dir, int up){
    HitsNode * aux;

    if(root->key == key){
        if(root->left && root->right){
            aux = successorHits(root->right);
            swapHits(root, aux, dir);
            aux->right = deleteHitsR(aux->right, key, parent, dir, up);

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
            if(up)
                root->key->hitsUp[dir] = NULL;
            else
                root->key->hitsLow[dir] = NULL;

            free(root);

            root = aux;
        }
    }
    else if(compareHits(root->key, key, dir)){
        root->left = deleteHitsR(root->left, key, parent, dir, up);        
        if(root->left)
            root->left->parent = root;
    }
    else{
        root->right = deleteHitsR(root->right, key, parent, dir, up);
        if(root->right)
            root->right->parent = root;
    }

    return root;
}

void insertHits(HitsNode * root, Item * key, int dir, int up){
    HitsNode * new = createHitsNode(key, dir, up);    
    
    if(root->parent) root->parent->parent = NULL;
    root->parent = insertHitsR(root->parent, new, dir);
    splayHits(new);
    root->parent = new;
    new->parent = root;
}

HitsNode * insertHitsR(HitsNode * root, HitsNode * no, int dir){
    if(!root)
        return no;

    if(compareHits(root->key, no->key, dir)){
        root->left = insertHitsR(root->left, no, dir);
        root->left->parent = root;
    }
    else{
        root->right = insertHitsR(root->right, no, dir);
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