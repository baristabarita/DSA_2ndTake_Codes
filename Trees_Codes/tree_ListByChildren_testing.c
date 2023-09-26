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

typedef struct{
    LIST Header[MAX];
    int Root;
}Dictionary;

//C. Function prototypes
void initDict(Dictionary *D);
void displayDict(Dictionary D);
int hash(int elem);
void insertDict(Dictionary *D, int elem);
void deleteDict(Dictionary *D, int elem);
int isMember(Dictionary D, int elem);
int parent(Dictionary D, int node);
//D. Function main
void main(){
    Dictionary D;
    printf("\n***** INITIALIZATION *****\n");
    initDict(&D);
    displayDict(D);
    printf("\n***** INSERT ELEMENTS *****\n");
    insertDict(&D, 55);
    insertDict(&D, 69);
    insertDict(&D, 420);
    insertDict(&D, 13);
    insertDict(&D, 83);
    insertDict(&D, 15);
    insertDict(&D, 25);
    insertDict(&D, 35);
    displayDict(D);
    printf("\n***** CHECK MEMBERSHIP *****\n");
    printf("Is 13 a Member of the Dictionary?: %d\n", isMember(D,13));
    printf("Is 20 a Member of the Dictionary?: %d\n", isMember(D,20));
    printf("\n\nLeft Most Child of node 5: %d", leftMem(D, 5));
    printf("\n\nLeft Most Child of node 7: %d", leftMem(D, 8));
    printf("\nParent of node 69: %d\n", parent(D, 69));
    printf("\nParent of node 83: %d\n", parent(D, 83));
    printf("\nParent of node 25: %d\n", parent(D, 25));
}
//E. Function definitions of the prototypes
void initDict(Dictionary *D){
    int index;
    for(index = 0; index < MAX; index++){
        D->Header[index] = NULL;
    }
}

void displayDict(Dictionary D){
    int index;
    LIST trav;
    for(index = 0; index < MAX; index++){
        printf("[%d] ", index);
        for(trav = D.Header[index]; trav != NULL; trav = trav->link){
            printf("%3d -> ", trav->data);
        }
        printf("NULL\n");
    }
}
int hash(int elem){
    return (elem % MAX);
}
void insertDict(Dictionary *D, int elem){
    int hashVal = hash(elem);
    LIST temp, *trav;
    for(trav = &D->Header[hashVal]; *trav != NULL && (*trav)->data != elem; trav = &(*trav)->link){}
    if(*trav == NULL){        
        temp = (LIST)malloc(sizeof(struct node));
        if(temp != NULL){
            temp->data = elem;
            temp->link = *trav;
            *trav = temp;
        }
    }
}
void deleteDict(Dictionary *D, int elem){
    int hashVal = hash(elem);
    LIST temp, *trav;
    for(trav = &D->Header[hashVal]; *trav != NULL && (*trav)->data != elem; trav = &(*trav)->link){}
    if(*trav != NULL){
        temp = *trav;
        *trav = temp->link;
        free(temp);
    }
}
int isMember(Dictionary D, int elem){
    int hashVal = hash(elem);
    LIST trav;
    for(trav = D.Header[hashVal]; trav != NULL && trav->data != elem; trav = trav->link){}
    return(trav == NULL)? 0 : 1;
}

/*
int leftMem(Dictionary D, int node){
    LIST trav;
    for(trav = D.Header[node]; trav != NULL && trav->link != NULL; trav = trav->link){}
    return(trav != NULL)? D.Header[node]->data : -1;
}*/


int leftMem(Dictionary D, int node){
    return(D.Header[node] != NULL && D.Header[node]->link != NULL)? D.Header[node]->data : -1;
}

int parent(Dictionary D, int node){
    int index;
    int retVal = -1;
    LIST trav;
    for(index = 0; index < MAX;){
        for(trav = D.Header[index]; trav != NULL && trav->data != node; trav = trav->link){}
        if(trav != NULL){
            retVal = index;
        }
        index++;
    }
    return retVal;
}