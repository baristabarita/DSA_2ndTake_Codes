/*
SET UID Linked List Implementation
*/
//A. Include files and macro definition
#include <stdio.h>
#include <stdlib.h>

//B. Data Structure definition
typedef struct node{
    int data;
    struct node*link;
} *SET;

//C. Function prototypes
void initSet(SET *S);
void displaySet(SET S);
void insertSet(SET *S, int elem);
void deleteSet(SET *S, int elem);
int isMember(SET S, int elem);
    //SET UID Ops
SET UnionSet(SET A, SET B);
SET IntersectionSet(SET A, SET B);
SET DifferenceSet(SET A, SET B);
int isSubset(SET A, SET B);

//D. Function main
void main(){
    SET A, B, C;

    printf("\n***** INITIALIZATION *****\n");
    initSet(&A);
    displaySet(A);
    initSet(&B);
    displaySet(B);

    printf("\n***** INSERT ELEMENTS *****\n");
    printf("\nSET A: ");
    insertSet(&A, 1);
    insertSet(&A, 2);
    insertSet(&A, 3);
    insertSet(&A, 6);
    displaySet(A);

    printf("\nSET B: ");
    insertSet(&B, 2);
    insertSet(&B, 4);
    insertSet(&B, 6);
    insertSet(&B, 9);
    displaySet(B);
    
    printf("\n***** UID OPERATIONS *****\n");
    printf("Union of Sets A and B: ");
    C = UnionSet(A,B);
    displaySet(C);
    printf("Intersection of Sets A and B: ");
    C = IntersectionSet(A,B);
    displaySet(C);
    printf("Difference of Sets A and B: ");
    C = DifferenceSet(A,B);
    displaySet(C);
    
    printf("\n***** DELETE ELEMENTS *****\n");
    deleteSet(&A, 3);
    displaySet(A);
    deleteSet(&B, 4);
    printf("\n***** CHECK MEMBERSHIP/ISSUBSET *****\n");
    printf("Is 1 Member of Set A? : %d\n", isMember(A,1));
    printf("Is 4 Member of Set B? : %d\n", isMember(B,4));
    printf("Is Set B a Subset of Set A? : %d\n", isSubset(A,B));
    
}
//E. Function definitions of the prototypes

void initSet(SET *S){
    *S = NULL;
}
void displaySet(SET S){
    SET trav;
    for(trav = S; trav != NULL; trav = trav->link){
        printf("%d -> ", trav->data);
    }
    printf("NULL\n");
}
void insertSet(SET *S, int elem){
    SET temp, *trav;
    for(trav = S; *trav != NULL && (*trav)->data < elem; trav = &(*trav)->link){}
    if(*trav != NULL && (*trav)->data == elem){
        //do nothing
    } else {
        temp = (SET)malloc(sizeof(struct node));
        if(temp != NULL){
            temp->data = elem;
            temp->link = *trav;
            *trav = temp;
        }
    }
}
void deleteSet(SET *S, int elem){
    SET temp, *trav;
    for(trav = S; *trav != NULL && (*trav)->data != elem; trav = &(*trav)->link){}
    if(trav != NULL){
        temp = *trav;
        *trav = temp->link;
        free(temp);
    }
}
int isMember(SET S, int elem){
    SET trav;
    for(trav = S; trav!= NULL && trav->data != elem; trav = trav->link){}
    return(trav == NULL) ? 0 : 1;
}
    //SET UID Ops
SET UnionSet(SET A, SET B){
    SET C, aptr, bptr, *cptr, temp;
    initSet(&C);
    for(aptr = A, bptr = B; aptr != NULL && bptr != NULL;){
        temp = (SET)malloc(sizeof(struct node));
        if(aptr->data <= bptr->data){
            //if both elems are the same, move bptr
            if(aptr->data == bptr->data){
                bptr = bptr->link;
            }
            temp->data = aptr->data;
            aptr = aptr->link;
        }else{
            //if elements of A are greater than/not equal to elems of B, copy data of B then move
            temp->data = bptr->data;
            bptr = bptr->link;
        }
        temp->link = NULL;
        (C == NULL) ? (C = temp) : (*cptr = temp);
        cptr = &(temp->link);
    }
    //set aptr to bptr if A is empty, otherwise keep it as is
    aptr = (aptr == NULL)? bptr : aptr;
    for(;aptr != NULL; aptr = aptr->link){
            temp = (SET)malloc(sizeof(struct node));
            temp->data = aptr->data;
            temp->link = NULL;
            (C == NULL) ? (C = temp) : (*cptr = temp);
            cptr = &(temp->link);
        }
    return C;
}
SET IntersectionSet(SET A, SET B){
    SET C, aptr, bptr, *cptr, temp;
    initSet(&C);
    for(aptr = A, bptr = B; aptr != NULL && bptr != NULL;){
        temp = (SET)malloc(sizeof(struct node));
        if(aptr->data <= bptr->data){
            if(aptr->data == bptr->data){
                temp->data = aptr->data;
                temp->link = NULL;
                (C == NULL)? (C = temp) : (*cptr = temp);
                cptr = &(temp)->link;
                bptr = bptr->link;
            }
            aptr = aptr->link;
        } else{
            bptr = bptr->link;
        }
    }
    return C;
}
SET DifferenceSet(SET A, SET B){
    SET C, aptr, bptr, *cptr, temp;
    initSet(&C);
    for(aptr = A, bptr = B; aptr != NULL && bptr != NULL;){
        if(aptr->data <= bptr->data){
            if(aptr->data != bptr->data){
                temp = (SET)malloc(sizeof(struct node));
                temp->data = aptr->data;
                temp->link = NULL;
                (C == NULL)? (C = temp) : (*cptr = temp);
                cptr = &(temp->link);
            } else{
                bptr = bptr->link;
            }
            aptr = aptr->link;
        } else {
            bptr = bptr->link;
        }
    }

    for(;aptr != NULL; aptr = aptr->link){
        temp = (SET)malloc(sizeof(struct node));
        temp->data = aptr->data;
        temp->link = NULL;
        (C == NULL)? (C=temp) : (*cptr = temp);
        cptr = &(temp->link);
    }
    return C;
}
int isSubset(SET A, SET B){
    SET aptr, bptr;
    for(aptr = A, bptr = B; aptr != NULL && bptr != NULL;){
        (aptr->data == bptr->data) ? (aptr = aptr->link) : (bptr = bptr->link);
    }
    return (aptr == NULL) ? 1 : 0;
}
