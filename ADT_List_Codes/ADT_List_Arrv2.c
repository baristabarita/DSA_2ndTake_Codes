/*
ADT LIST Array Implementation Version 2
Version 2: List is a pointer to a structure containing
           an array and a variable count
*/

//A. Include files and macro definition
#include<stdio.h>
#include<stdlib.h>
#define MAX 10
//B. Data Structure definition
typedef struct node{
    char elem[MAX];
    int count;
}*LIST;
//C. Function prototypes
void initList(LIST *L);
void insertFirst(LIST *L, char data);
void insertLast(LIST *L, char data);
void insertSorted(LIST *L, char data);
void deleteFirst(LIST *L);
void deleteLast(LIST *L);
void deleteAllOccur(LIST *L, char data);
int isMember(LIST L, char data);
void displayList(LIST L);

//D. Function main
void main(){
    LIST L;
    printf("\n****** List Initialization ******\n");
    initList(&L);
    displayList(L);
    printf("\n****** Inserting Elements ******\n");
    insertFirst(&L, 'a');
    insertFirst(&L, 'b');
    insertLast(&L, 'z');
    insertSorted(&L, 'p');
    insertSorted(&L, 'c');
    insertSorted(&L, 'p');
    displayList(L);
    printf("\n"); 
    printf("\n****** Deleting elements ******\n");
    deleteFirst(&L);
    deleteAllOccur(&L, 'p');
    deleteLast(&L);
    displayList(L);
    printf("\n");
    printf("\n****** Check Member ******\n");
    printf("is 'a' a member?: %d\n", isMember(L, 'a'));
    printf("is 'o' a member?: %d\n", isMember(L, 'o'));
}
//E. Function definitions of the prototypes
void initList(LIST *L){
    *L = (LIST)malloc(sizeof(struct node));
    if((*L)!=NULL){
        (*L)->count = 0;
    }
}
void insertFirst(LIST *L, char data){
    int index;

    if((*L)->count != MAX){
        for(index = (*L)->count; index > 0; index--){
            //shift existing element downwards
            (*L)->elem[index] = (*L)->elem[index-1];
        }
        (*L)->elem[0] = data;
        (*L)->count++;
    }
}
void insertLast(LIST *L, char data){
    if((*L)->count != MAX){
        (*L)->elem[(*L)->count] = data;
        (*L)->count++;
    }
}
void insertSorted(LIST *L, char data){
    int trav, index;
    if((*L)->count != MAX){
        for(trav = 0; trav < (*L)->count && 
                      (*L)->elem[trav] < data; trav++){}
        if(trav != (*L)->count){
            for(index = (*L)->count; 
                index >= trav; index--){
                (*L)->elem[index] = (*L)->elem[index-1];
            }
        }
        (*L)->elem[trav] = data;
        (*L)->count++;
    }
}
void deleteFirst(LIST *L){
    int index;
    if((*L)->count != 0){
        for(index = 0; index < (*L)->count; index++){
            (*L)->elem[index] = (*L)->elem[index+1];
        }
        (*L)->count--;
    }
}

void deleteLast(LIST *L){
    if((*L)->count != 0){
        (*L)->count--;
    }
}
void deleteAllOccur(LIST *L, char data){
    int trav, index;
    if((*L)->count != 0){
        for(trav = 0; trav < (*L)->count;){
            if((*L)->elem[trav] == data){
                for(index = trav+1; index < (*L)->count; index++){
                    (*L)->elem[index-1] = (*L)->elem[index];
                }
                (*L)->count--;
            } else {
                trav++;
            }
        }
    }
}
int isMember(LIST L, char data){
    int index;
    for(index = 0; index < MAX && L->elem[index] != data; index++){}
    return (index != MAX)? 1 : 0;
}
void displayList(LIST L){
    int index;
    for(index = 0; index < L->count; index++){
        printf("%c ", L->elem[index]);
    }
    if(L->count == 0){
        printf("\nEMPTY LIST\n");
    } 
}