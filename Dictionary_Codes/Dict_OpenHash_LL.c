/*
Dictionary Open-Hashing Linked List Implementation
*/
//A. Include files and macro definition
#include <stdio.h>
#include <stdlib.h>
#define MAX 10

//B. Data Structure definition
typedef struct node{
    int data;
    struct node *link;
}*LIST;

typedef LIST Dictionary[MAX];

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
    printf("\n***** INSERT ELEMENTS *****\n");
    insertDict(D, 55);
    insertDict(D, 69);
    insertDict(D, 420);
    insertDict(D, 13);
    insertDict(D, 83);
    displayDict(D);
    printf("\n***** DELETING ELEMENTS *****\n");
    deleteDict(D, 55);
    displayDict(D);
    printf("\n***** CHECK MEMBERSHIP *****\n");
    printf("Is 13 a Member of the Dictionary?: %d\n", isMember(D,13));
    printf("Is 20 a Member of the Dictionary?: %d\n", isMember(D,20));
}
//E. Function definitions of the prototypes
void initDict(Dictionary D){
    int index;
    for(index = 0; index < MAX; index++){
        D[index] = NULL;
    }
}

void displayDict(Dictionary D){
    int index;
    LIST trav;
    for(index = 0; index < MAX; index++){
        printf("[%d] ", index);
        for(trav = D[index]; trav != NULL; trav = trav->link){
            printf("%3d -> ", trav->data);
        }
        printf("NULL\n");
    }
}
int hash(int elem){
    return (elem % MAX);
}
void insertDict(Dictionary D, int elem){
    int hashVal = hash(elem);
    LIST temp, *trav;
    for(trav = &D[hashVal]; *trav != NULL && (*trav)->data != elem; trav = &(*trav)->link){}
    if(*trav == NULL){        
        temp = (LIST)malloc(sizeof(struct node));
        if(temp != NULL){
            temp->data = elem;
            temp->link = *trav;
            *trav = temp;
        }
    }
}
void deleteDict(Dictionary D, int elem){
    int hashVal = hash(elem);
    LIST temp, *trav;
    for(trav = &D[hashVal]; *trav != NULL && (*trav)->data != elem; trav = &(*trav)->link){}
    if(*trav != NULL){
        temp = *trav;
        *trav = temp->link;
        free(temp);
    }
}
int isMember(Dictionary D, int elem){
    int hashVal = hash(elem);
    LIST trav;
    for(trav = D[hashVal]; trav != NULL && trav->data != elem; trav = trav->link){}
    return(trav == NULL)? 0 : 1;
}