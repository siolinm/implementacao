#include"cands.h"

#define minimum(a, b, dir) (getX(a, dir) > getX(b, dir) ? b : a)

CandsNode * createCandsNode(Item * key){
    CandsNode * new = malloc(sizeof(*new));
    new->left = new->right = NULL;
    new->parent = NULL;
    new->key = key;
    return new;
}

CandsNode * initCands(Item * p){
    return createCandsNode(p);
}


/* attachs the joinRoot subtree to tree with root root */
CandsNode * joinCands(CandsNode * root, CandsNode * joinRoot, int dir){

}

/* searchs for up/low(p) in the tree with root root and returns a subtree containing all nodes above/beside*/
CandsNode * cutCands(CandsNode * root, Item * p, int uplow, int dir){

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

CandsNode * insertCands(CandsNode * root, Item * key, int direction){
    CandsNode * new = createCandsNode(key);
    CandsNode * parent = root, *x;
    
    root = insertCandR(root, new, direction);
    splayCand(new);

    return root;
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
    if(root->left && root->right){
        leftmost = minimum(root->left->key, root->right->key, dir);
    }
    else if(root->left){
        leftmost = minimum(root->left->leftmost->key, root->left->key, dir);
    }
    else if(root->right){
        leftmost = minimum(root->right->leftmost->key, root->right->key, dir);        
    }
    else
    {
        leftmost = root;
    }
    
    root->leftmost = leftmost;

    return root;
}

void splayCands(CandsNode * x){
    while(x && x->parent){
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