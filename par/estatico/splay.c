#include"splay.h"

root = NULL;

Node * splayNode = NULL;

Node * createNode(Item * key){
    Node * new = malloc(sizeof(*new));
    new->left = new->right = NULL;
    new->parent = NULL;
    new->key = key;
    return new;
}

void rotateLeft(Node * x){
    Node * aux, *parent;
    
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
    else
        root = aux;

}

void rotateRight(Node * x){
    Node * aux, *parent;
    
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
    else
        root = aux;
}

void query(Item * key){
    Node * x = root;
    while(x && x->key != key) {
        if(compare(x->key, key))
            x = x->left;
        else
            x = x->right;
    }

    if(x != NULL)
        splay(x);
}

Node * queryLow(Node * start){
    Node *x = start;

    
}

Node * queryUp(Node * start){    

}

void insert(Item * key){
    Node * new = createNode(key);
    Node * parent = root, *x;
    
    if(root == NULL){
        root = new;
        return;
    }

    if(compare(parent->key, new->key))
        x = parent->left;
    else
        x = parent->right;

    while(x != NULL){
        parent = x;
        if(compare(x->key, new->key))
            x = x->left;
        else
            x = x->right;
    }

    if(compare(parent->key, new->key))
        parent->left = new;
    else
        parent->right = new;
    
    new->parent = parent;
    splay(new);
}

void splay(Node * x){
    while(x->parent){
        /*
            l or r case
        */
        if(!x->parent->parent){
            if(x->parent->left == x)
                rotateRight(x->parent);
            else
                rotateLeft(x->parent);
        }
        else{
            if(x->parent->left == x){
                /* rr case*/
                if(x->parent->parent->left == x->parent){
                    rotateRight(x->parent->parent);
                    rotateRight(x->parent);
                }
                else{
                    /* rl case */
                    rotateRight(x->parent);
                    rotateLeft(x->parent);
                }
            }
            else{
                /* lr case */
                if(x->parent->parent->left == x->parent){
                    rotateLeft(x->parent);
                    rotateRight(x->parent);
                }
                else{
                    /* ll case */
                    rotateLeft(x->parent->parent);
                    rotateLeft(x->parent);
                }
            }
        }
    }
}

int compare(Item * a, Item * b){
    if(getYCoordinate(a) > getYCoordinate(b))
        return 1;
    return 0;
}