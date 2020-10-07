#include"cands.h"

#define minimum(a, b) (getXCoordinate(a) > getXCoordinate(b) ? b : a)

CandsNode * createCandsNode(Item * key){
    CandsNode * new = malloc(sizeof(*new));
    new->left = new->right = NULL;
    new->parent = NULL;
    new->key = key;
    return new;
}

void rotateLeft(CandsNode * x){
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

void rotateRight(CandsNode * x){
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
    else
        root = aux;
}

CandsNode * queryLow(Item * p, CandsNode * start){
    CandsNode *x = start, *low;
    low = NULL;
    while(x){
        /* I go down while the points are above or in the line */
        while(x && checkLine(p, x->key, -0.5*PI_3) >= 0)
            x = x->left;

        /* x should now be the first point that i found below the line */
        while(x && x->right && checkLine(p, x->right->key, -0.5*PI_3) == -1)
            x = x->right;
        
        if(x){
            low = x;
            x = x->right;
            if(!(x && checkLine(p, x->key, -0.5*PI_3) >= 0))
                x = NULL;
        }
    }
    
    return low;
}

CandsNode * queryUp(Item * p, CandsNode * start){    
    CandsNode *x = start, *up;
    up = NULL;
    
    while(x){
        /* I go up while the points are below the line */
        while(x && checkLine(p, x->key, 0.5*PI_3) == -1)
            x = x->right;
        

        /* x should now be the first point that i found above or in the line */
        /* I go down while the points are above or in the line*/
        while(x && x->left && checkLine(p, x->left->key, 0.5*PI_3) >= 0)
            x = x->left;

        if(x){
            up = x;
            x = x->left;
            if(!(x && checkLine(p, x->key, 0.5*PI_3) == -1))
                x = NULL;            
        }
    }

    return up;
}

CandsNode * cands(Item * p){
    CandsNode * x, *lowCandsNode, *lcandsRoot;
    int low = 0;
    if(!root)
        return NULL;
    x = queryLow(p, root);

    if(x){
        low = 1;
        splay(x);
        lowCandsNode = x;
    }

    if(!low){
        x = queryUp(p, root);
    }
    else{
        x = queryUp(p, root->right);
        if(root->right)
            root->right->parent = NULL;
    }

    if(x){
        splay(x);        
        lcandsRoot = x->left;
        x->left = NULL;
        if(low){
            root = lowCandsNode;
            root->right = x;
            x->parent = root;
        }
    }
    else{
        if(low){
            lcandsRoot = root->right;
            root->right = NULL;
        }
        else{
            lcandsRoot = root;
            root = NULL;
        }
    }

    return lcandsRoot;
}


CandsNode * insertCand(CandsNode * root, Item * key, int direction){
    CandsNode * new = createCandsNode(key);
    CandsNode * parent = root, *x;
    
    root = insertCandR(root, new, direction);
    splayCand(new);


    return root;
}

CandsNode * insertCandR(CandsNode * root, CandsNode * no, int dir){
    if(!root)
        return no;

    if(compare(root->key, no)){
        root->left = insertCandR(root->left, no, dir);
        root->left->parent = root;
    }
    else{
        root->right = insertCandR(root->right, no, dir);
        root->right->parent = root;
    }

    return root;
}

void splayCand(CandsNode * x){
    while(x && x->parent){
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

void freeAll(CandsNode * r){
    if(r != NULL){
        freeAll(r->left);
        freeAll(r->right);        
        free(r);
    }
    root = NULL;
}

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
        for(i = 0; i < size; i++)
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