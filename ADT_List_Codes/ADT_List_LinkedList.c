/*
ADT LIST Linked List Implementation
*/

//A. Include files and macro definition
#include <stdio.h>
#include <stdlib.h>

//B. Data Structure definition
typedef struct node{
    char data;
    struct node *link;
}*LIST;
//C. Function prototypes
void initList(LIST *L);
void insertFirst(LIST *L, char elem);
void insertLast(LIST *L, char elem);
void insertSorted(LIST *L, char elem);
void deleteFirst(LIST *L);
void deleteLast(LIST *L);
void deleteAllOccur(LIST *L, char elem);
int isMember(LIST L, char elem);
void displayList(LIST L);
//D. Function main
void main(){
    LIST L;

    printf("\n****** List Initialization ******\n");
    initList(&L);
    displayList(L);
    printf("\n****** Inserting Elements ******\n");
    insertFirst(&L, 'b');
    insertFirst(&L, 'a');
    insertLast(&L, 'z');
    insertSorted(&L, 'l');
    insertLast(&L, 'm');
    insertSorted(&L, 'l');
    displayList(L);
    printf("\n****** Deleting elements ******\n");
    deleteFirst(&L);
    deleteLast(&L);
    deleteAllOccur(&L, 'l');
    displayList(L);
    printf("\n****** Check Member ******\n");
    printf("is 'a' a member?: %d\n", isMember(L, 'a'));
    printf("is 'b' a member?: %d\n", isMember(L, 'b'));
    printf("is 'o' a member?: %d\n", isMember(L, 'o'));
    
}
//E. Function definitions of the prototypes
void initList(LIST *L){
    *L = NULL;
}
void insertFirst(LIST *L, char elem){
    LIST temp = (LIST)malloc(sizeof(struct node));
    if(temp != NULL){
        temp->data = elem;
        temp->link = *L;
        *L = temp;
    }
}
void insertLast(LIST *L, char elem){
    LIST temp = (LIST)malloc(sizeof(struct node));
    LIST *trav;
    for(trav = L; (*trav) != NULL; trav = &(*trav)->link){}
    if(temp != NULL){
        temp->data = elem;
        temp->link = *trav;
        *trav = temp;
    }
}
void insertSorted(LIST *L, char elem){
    LIST temp = (LIST)malloc(sizeof(struct node));
    LIST *trav;
    for(trav = L;(*trav)!= NULL && (*trav)->data < elem; trav = &(*trav)->link){}
    if(temp != NULL){
        temp->data = elem;
        temp->link = *trav;
        *trav = temp;
    }
}
void deleteFirst(LIST *L){
    LIST temp;
    if((*L)!= NULL){
        temp=*L;
        *L = temp->link;
        free(temp);
    }
}
void deleteLast(LIST *L){
    LIST temp;
    LIST *trav;
    for(trav = L; (*trav)->link != NULL; trav = &(*trav)->link){}
    if((*trav) != NULL){
        temp=*trav;
        *trav = temp->link;
        free(temp);
    }
}
void deleteAllOccur(LIST *L, char elem){
    LIST *trav, temp;
        for(trav = L; *trav!=NULL;){
            if((*trav)->data == elem){
                temp = *trav;
                *trav = temp->link;
                free(temp);
            }else{
                trav = &(*trav)->link;
            }
        }
    }
int isMember(LIST L, char elem){
    LIST trav;
    for(trav = L; trav != NULL && trav->data != elem; trav = trav->link){}
    return(trav != NULL)? 1 : 0;
}
void displayList(LIST L){
    LIST trav;
    for(trav = L; trav != NULL; trav = trav->link){
       printf("%c -> ", trav->data); 
    }
    printf("NULL\n");
}