#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int node;
    struct node* LC;
    struct node* RC;
}*BST;

void INIT(BST *T);
void INSERT(BST *T, int elem);
void DELETE(BST *T, int elem);
int ISMEMBER(BST T, int elem);
int MIN(BST T);
int MAX(BST T);

void PREORDER(BST T);
void INORDER(BST T);
void POSTORDER(BST T);

void main(){
    printf("\n - - Initialize BST Tree - - \n");
    BST T;
    INIT(&T);

    printf("\n - - Insert Nodes of SET T = {10, 5, 14, 12, 7, 18, 15} - -\n");
    INSERT(&T, 10);
    INSERT(&T, 5);
    INSERT(&T, 14);
    INSERT(&T, 12);
    INSERT(&T, 7);
    INSERT(&T, 18);
    INSERT(&T, 15);

    printf("\n - - Display Traversals - - \n");
    printf("\nPREORDER : ");
    PREORDER(T);
    printf("\nINORDER : ");
    INORDER(T);
    printf("\nPOSTORDER : ");
    POSTORDER(T);
}

void INIT(BST *T){
    *T = NULL;
}
void INSERT(BST *T, int elem){
    BST *trav, temp;
    for(trav = T; *trav != NULL && (*trav)->node != elem;){
        trav = ((*trav)->node > elem)? &(*trav)->LC : &(*trav)->RC; 
    }
    if(*trav == NULL){
        temp = (BST)malloc(sizeof(struct node));
        if(temp != NULL){
            temp->node = elem;
            temp->LC = *trav;
            temp->RC = *trav;
            *trav = temp;
        }
    }
}
void DELETE(BST *T, int elem){
    BST *trav, *trav2, temp;
    if(*T != NULL){
        for(trav = T; (*trav) != NULL && (*trav)->node != elem;){
            trav = ((*trav)->node > elem)? &(*trav)->LC : &(*trav)->RC;
        }
        if((*trav)->LC != NULL && (*trav)->RC != NULL){ //if two children
            for(trav2 = &(*trav)->RC; (*trav2)->LC != NULL; trav2 = &(*trav2)->LC){} //find
            temp = *trav2;
            *trav2 = temp->RC;
            (*trav)->node = temp->node;
            free(temp);
        } else { //one child or is a leaf
            temp = *trav;
            *trav = ((*trav)->LC == NULL)? (*trav)->RC : (*trav)->LC;
            free(temp);
        }
    } else {
        *T = NULL;
    }
}
int ISMEMBER(BST T, int elem){
    BST trav;
    for(trav = T; trav != NULL && trav->node != elem;){
        trav = (trav->node > elem) ? trav->LC : trav->RC;
    }
    return(trav == NULL)? 0 : 1;
}
int MIN(BST T){
    BST trav;
    for(trav = T; trav != NULL; trav = trav->LC){}
    return trav->node;
}
int MAX(BST T){
    BST trav;
    for(trav = T; trav != NULL; trav = trav->RC){}
    return trav->node;
}

void PREORDER(BST T){
    if(T != NULL){
        printf("%d ", T->node);
        PREORDER(T->LC);
        PREORDER(T->RC);
    }
}

void INORDER(BST T){
    if(T != NULL){
        INORDER(T->LC);
        printf("%d ", T->node);
        INORDER(T->RC);
    }
}
void POSTORDER(BST T){
    if(T != NULL){
        POSTORDER(T->LC);
        POSTORDER(T->RC);
        printf("%d ", T->node);
    }
}