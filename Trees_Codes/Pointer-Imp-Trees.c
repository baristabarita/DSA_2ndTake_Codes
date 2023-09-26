//Non - Recursive Functions

#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int elem;
    struct node* LC;
    struct node* RC;
}*BST;

void INITIALIZE(BST *T);
void INSERT(BST *T, int node);
void DELETE(BST *T, int node); 
int MEMBER(BST T, int node);
int MIN(BST T);
int MAX(BST T);

void main(){
    printf("\n - - Initialization of BST Tree - - \n");
    BST T;
    INITIALIZE(&T);

    printf("\n - - Insert Nodes of Set T = {10,5,14,12,7,18,15} - - \n");
    INSERT(&T, 10);
    INSERT(&T, 5);
    INSERT(&T, 14);
    INSERT(&T, 12);
    INSERT(&T, 7);
    INSERT(&T, 18);
    INSERT(&T, 15);
    
    printf("\n - - Deleting Nodes - - \n");
    DELETE(&T, 7); // Deleting a leaf
    DELETE(&T, 5); // Deleting a right child only
    DELETE(&T, 18); // Deleting a left child only
    DELETE(&T, 10);

    //printf("\n - - Membership Check - - \n");
    
}

void INITIALIZE(BST *T){
    *T = NULL;
}
void INSERT(BST *T, int node){
    BST *trav;
    for(trav = T; *trav != NULL && (*trav)->elem != node; ){
        //if the element in trav is less than the new node, go to RC, else go to LC
        trav = ((*trav)->elem < node) ? &(*trav)->RC : &(*trav)->LC;
    }
    if(*trav == NULL){
        //calloc is used since we are always inserting a leaf, meaning we always isnert at the bottom and has no children
        *trav = (BST)calloc(1, sizeof(struct node));
        if(*trav != NULL){
            (*trav)->elem = node;
        }

        /* Malloc Version
        BST temp = (BST)(malloc(sizeof(struct node)));
        if(temp != NULL){
            temp->elem = node;
            temp->LC = *trav;
            temp->RC = *trav;
            *trav = temp;
        }
        */

    }
}
void DELETE(BST *T, int node){
    BST *trav, *trav2, temp;

    if(*T != NULL){
        
    }
}
int MEMBER(BST T, int node){
    BST trav;
    for(trav = T; trav != NULL && trav->elem != node;){
        trav = (trav->elem > node)? trav->LC : trav->RC;
    }
    return(trav == NULL)? 0 : 1;
}
int MIN(BST T){
    BST trav;
    for(trav = T; trav != NULL; trav = trav->LC){}
    return trav->elem;
}
int MAX(BST T){
    BST trav;
    for(trav = T; trav != NULL; trav = trav->RC){}
    return trav->elem;
}