#include"tourn.h"

int compareTourn(int i, int j){
    double a, b;
    a = distance(tourn[i]->p, tourn[i]->lcandp, tourn[i]->direction);
    b = distance(tourn[j]->p, tourn[j]->lcandp, tourn[j]->direction);
    return a < b;
}

void initTourn(){
    tournElem = 3*n;
    int i = 2*tournElem - 1;
    int dir;

    while(i > 1){
        if(compareTourn(i, i - 1)){
            tourn[i/2] = tourn[i];
            dir = tourn[i-1]->direction;
            tourn[i - 1]->p->lastMatch[dir] = i - 1;
        }
        else{
            tourn[i/2] = tourn[i - 1];
            dir = tourn[i]->direction;
            tourn[i]->p->lastMatch[dir] = i;
        }

        i = i - 2;
    }

    dir = tourn[1]->direction;
    tourn[1]->p->lastMatch[dir] = 1;
}

/*
    minimum size has to be at least 2
*/
void resizeTourn(){
    int i;
    TournObject ** newTourn;
    newTourn = malloc((2*tournMaxSize + 1)*sizeof(*newTourn));

    for (i = 1; i <= tournElem; i++){
        newTourn[i] = tourn[i];
    }

    newTourn = tourn;
    tournMaxSize = 2*tournMaxSize;
}

void insertTourn(TournObject * obj, int dir){
    int i, k;
    int dir;

    if(2*tournElem + 1 == tournMaxSize)
        resizeTourn();
    tournElem++;

    i = 2*tournElem - 1;

    tourn[i] = obj;
    tourn[i - 1] = tourn[i/2];
    
    k = i - 1;

    while(i > 1 && compareTourn(i, k)){
        tourn[i/2] = tourn[i];
        dir = tourn[k]->p->lastMatch[dir];
        tourn[k]->p->lastMatch[dir] = k;
        update(tourn[k]);
        
        i = i/2;
        k = 2*(i/2) + !(i % 2);
    }

    dir = tourn[i]->p->lastMatch[dir];
    tourn[i]->p->lastMatch[dir] = i;    
}

void deleteTourn(TournObject * obj){
    int k, j, i, dir;
    dir = obj->direction;
    i = obj->p->lastMatch[dir];

    /*
        Looks for the "first match" that obj played
    */
    j = i;
    k = 2*(j/2) + !(j % 2);

    if(2*j < 2*tournElem - 1){
        while(j < 2*tournElem - 1){
            if(j > 1 && tourn[j] != tourn[j/2])
                j = k;
            
            j = 2*j;
            k = 2*(j/2) + !(j % 2);
        }

        j = j/2;
        k = 2*(j/2) + !(j % 2);
    }

    /*
        Looks for a object to substitute the removed one.
        The object that will substitute the removed object is 
        the one who lost the match between the two last positions.
        If the object that is being removed is already at one of the two last positions
        remove the two last positions and make his brother go up
    */
    if(j == 2*tournElem - 1 || j == 2*tournElem - 2){
        tourn[j/2] = tourn[k];
        tourn[j] = tourn[k] = NULL;
        j = j/2;
        k = 2*(j/2) + !(j % 2);
    }
    else{
        if(tourn[2*tournElem - 1] == tourn[tournElem - 1])
            tourn[j] = tourn[2*tournElem - 2];
        else
            tourn[j] = tourn[2*tournElem - 1];

        tourn[2*tournElem - 1] = tourn[2*tournElem - 2] = NULL;
    }

    /*
        Goes up fixing matches, j is the winner and k is the loser of the match
    */
    while(j > 1){
        if(!compareTourn(j, k)){
            i = k;
            k = j;
            j = i;
        }

        tourn[j/2] = tourn[j];
        dir = tourn[k]->direction;
        tourn[k]->p->lastMatch[dir] = k;
        update(tourn[k]);
        
        j = j/2;
        k = 2*(j/2) + !(j % 2);
    }

    dir = tourn[j]->direction;
    tourn[j]->p->lastMatch[dir] = j;
    update(tourn[j]);
}