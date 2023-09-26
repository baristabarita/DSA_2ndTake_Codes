/*
Dictionary Closed Hashing Linear Hashing Implementation
*/
//A. Include files and macro definition
#include <stdio.h>
#include <stdlib.h>
#define MAX 10
#define EMPTY 0
#define DELETED -1

//B. Data Structure definition
typedef int Dictionary[MAX];

//C. Function prototypes
void initDict(Dictionary D);
void displayDict(Dictionary D);
int hash(int elem);
void insertDict(Dictionary D, int elem);
void deleteDict(Dictionary D, int elem);
int isMember(Dictionary D, int elem);

//D. Function main
void main(){
    Dictionary D;
    printf("\n***** INITIALIZATION *****\n");
    initDict(D);
    displayDict(D);

    printf("***** INSERT ELEMENTS *****\n");
    insertDict(D, 33);
    insertDict(D, 69);
    insertDict(D, 73);
    insertDict(D, 14);
    insertDict(D, 19);
    displayDict(D);
    printf("***** DELETE ELEMENTS *****\n");
    deleteDict(D, 33);
    displayDict(D);
    printf("\n**** CHECK MEMBERSHIP ****\n");
    printf("is 69 a part of Dictionary D?: %d\n", isMember(D,69));
    printf("is 45 a part of Dictionary D?: %d\n", isMember(D,45));
    
}
//E. Function definitions of the prototypes
void initDict(Dictionary D){
    int index;
    for(index = 0; index < MAX; index++){
        D[index] = EMPTY;
    }
}
void displayDict(Dictionary D){
    int index;
    printf("\n INDEX     ELEMENT  HASH VALUE ");
    for(index = 0; index < MAX; index++){
        printf("\n[%d] ", index);
        if(D[index] == EMPTY){
            printf("%12s ", "EMPTY");
        } else if (D[index] == DELETED){
            printf("%12s ", "DELETED");
        }
        else{
            printf("%9d ", D[index]);
        }
        if(D[index] == EMPTY || D[index] == DELETED){
            printf("%9d ", 0);
        }else{
            printf("%9d", hash(D[index]));
        }
    }
}
int hash(int elem){
    return(elem % MAX);
}
void insertDict(Dictionary D, int elem){
    int hashVal = hash(elem);
    int temp;
    if(D[hashVal] != elem){
        for(temp = hashVal; D[temp] != elem && D[temp] != EMPTY && D[temp] != DELETED; temp = (temp+1)%MAX){}
        D[temp] = elem;
    }
}
void deleteDict(Dictionary D, int elem){
    int hashVal = hash(elem);
    int temp = hashVal;
    if(D[temp] != elem){
        for(temp = hashVal+1; D[temp] != elem && D[temp] != EMPTY && D[temp] != DELETED; temp = (temp+1)%MAX){}
    }
    D[temp] = DELETED;
}
int isMember(Dictionary D, int elem){
    int hashVal = hash(elem);
    int temp, counter;
        for(temp = hashVal, counter = 1; counter < MAX && D[temp] != EMPTY && D[temp] != elem; counter++, temp = (temp+1) % MAX){}
        return (D[temp] != EMPTY && counter < MAX)? 1 : 0;
    
}
