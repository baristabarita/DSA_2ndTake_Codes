#include<stdio.h>

#define DELETED '*'
#define EMPTY '!'
#define MAX 10

typedef char Dictionary [MAX];
typedef enum{TRUE, FALSE} boolean;

void initDict(Dictionary *D){
    int index;
    for(index = 0; index < MAX; index++){
        D[index] == EMPTY;
    }
}
boolean isMember(char elem, Dictionary D){
    boolean retval = FALSE;
    int hashVal = hash(elem), trav;
    if(D[hashVal] != elem){
        for(trav = hashVal+1; trav!=EMPTY && D[trav]!=elem; trav = (trav+1)%MAX){}
        if(trav!=hashVal){
            retval = TRUE;
        }
    } else{
        retval = TRUE;
    }
    return retval;
}
void main(){
    
}