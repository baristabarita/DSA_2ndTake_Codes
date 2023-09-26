//DSA Tutorials
#include<stdio.h>
#include<stdlib.h>

//Data Structure Definition of List
typedef struct node{
    char data;
    struct node* link;
}Node, *List;

//Function Prototypes Here
void initList(List *A);
void display(List A);
void insertFirst(List *A, char elem);
void insertLast(List *A, char elem);
void insertSorted(List *A, char elem);
int searchElem(List A, char elem);
void deleteElem(List *A, char elem);

//Main Function Here
void main(){
    List L;
    initList(&L);
    insertFirst(&L, 'U');
    insertFirst(&L, 'S');
    insertFirst(&L, 'C');
    display(L);
    int checkElem = searchElem(L, 'U');
    printf("\nFound Elem: %d\n", checkElem);
    deleteElem(&L, 'C');
    display(L);
    printf("\nAfter Insert first:  ");
    insertFirst(&L,'P');
    display(L);
}


//Function Definitions Here
void initList(List *A){
    *A = NULL;
}

void display(List A){
    List trav;
    for (trav = A; trav != NULL; trav = trav->link){
        printf("%c", trav->data);
    }
}

void insertLast(List *A, char elem){
    List *trav, temp;

    for(trav = A; *trav != NULL; trav = &(*trav)->link){}
    //1. Dynamically allocate space for a new node
    temp = (List)malloc(sizeof(struct node));
    if(temp != NULL){
    //2. Assign the data to the node
    temp->data = elem;
    //3. Link the node to the remainder of the List
    temp->link = *trav;
    //4. Link the area of isolation to the new node
    *trav = temp;
    }
}

void insertSorted(List *A, char elem){
    List *trav, temp;

    for(trav=A; *trav != NULL && (*trav)->data < elem; trav = &(*trav)->link){}
    temp = (List)malloc(sizeof(struct node));
    if(temp!=NULL){
        temp->data = elem;
        temp->link = *trav;
        *trav = temp;
    }
}
void insertFirst(List *A, char elem){
    List temp;

    temp = (List)malloc(sizeof(struct node));
    if(temp!=NULL){
        temp->data = elem;
        temp->link = *A;
        *A = temp;
    }
}

int searchElem(List A, char elem){
    List trav;
    for(trav=A; trav!=NULL && trav->data != elem; trav = trav->link){}
    return(trav!=NULL)? 1 : 0;
}

void deleteElem(List *A, char elem){
    List *trav, temp;
    for(trav=A; (*trav)!= NULL && (*trav)->data!= elem; 
                trav = &(*trav)->link){}
    if(*trav != NULL){
    //1. Let temp hold the node to be removed
    temp = *trav;
    //2. Link the node before temp to the node after temp
    *trav = temp->link;
    //3. F w e e the memory space consumed by temp
    free(temp);
    }
}