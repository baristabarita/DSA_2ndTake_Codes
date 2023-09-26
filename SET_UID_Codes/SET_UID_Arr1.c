/*
SET UID ARRAY Implementation
Note: This variation uses Array List Structure w/ count field
*/
//A. Include files and macro definition
#include <stdio.h>
#include <stdlib.h>
#define MAX 20

//B. Data Structure definition
typedef struct{
    int data[MAX];
    int count;
}SET;
typedef enum{TRUE, FALSE} boolean;

//C. Function prototypes
void initSet(SET *S);
void displaySet(SET S);
void insertSet(SET *S, int elem);
void deleteSet(SET *S, int elem);
boolean isMember(SET S, int elem);
    //SET UID OPERATIONS
SET UnionSet(SET A, SET B);
SET IntersectionSet(SET A, SET B);
SET DifferenceSet(SET A, SET B);
boolean isSubset(SET A, SET B);

//D. Function main
void main(){
    SET A;
    SET B;
    printf("\n***** INITIALIZE *****\n");
    initSet(&A);
    displaySet(A);
    initSet(&B);
    displaySet(B);

    printf("\n***** INSERT ELEMENTS TO SET *****\n");
    printf("Inserting Set A: \n");
    insertSet(&A, 1);
    insertSet(&A, 2);
    insertSet(&A, 3);
    insertSet(&A, 5);
    insertSet(&A, 6);
    
    displaySet(A);
    printf("\nInserting Set B: \n");
    insertSet(&B, 2);
    insertSet(&B, 3);
    insertSet(&B, 7);
    insertSet(&B, 8);
    insertSet(&B, 10);
    displaySet(B);
    
    printf("\n***** SET UID OPERATION *****\n");
    printf("\n >> Union of Sets A and B: \n");
    SET C = UnionSet(A,B);
    displaySet(C);
    printf("\n >> Intersection of Sets A and B: \n");
    C = IntersectionSet(A,B);
    displaySet(C);
    printf("\n >> Difference of Sets A and B: \n");
    C = DifferenceSet(A,B);
    displaySet(C);
     printf("\n***** DELETE ELEMENTS IN SET *****\n");
    printf("\nDeleting in Set A: \n");
    deleteSet(&A, 1);
    deleteSet(&A, 2);
    displaySet(A);
    printf("\nDeleting in Set B: \n");
    deleteSet(&B, 7);
    deleteSet(&B, 3);
    displaySet(B);
    
    printf("\n***** CHECK MEMBERSHIPS AND ISSUBSET *****\n");
    printf("is 3 a member of set A? : %d\n", isMember(A, 3));
    printf("is 7 a member of set B? : %d\n", isMember(B, 7));
    printf("Is B a subset of A?: %d", isSubset(A,B));
}

//E. Function definitions of the prototypes
void initSet(SET *S){
    S->count = 0;
}
void displaySet(SET S){
    int index;
    for(index = 0; index < S.count; index++){
        printf("%d ", S.data[index]);
    }
}

void insertSet(SET *S, int elem){
    int temp, trav;
    for(trav = 0; S->count < MAX && trav < S->count && S->data[trav] < elem;  trav++){}
        if(S->count > 0){
            //to shift downwards
            if(trav < MAX && S->data[S->count-1] != elem){
                for(temp = trav, trav = S->count+1; trav > temp; trav--){
                    S->data[trav] = S->data[trav-1];
                }
            }
        }
        S->data[trav] = elem;
        S->count++;
}

void deleteSet(SET *S, int elem){
    int index;

    for(index = 0; index < S->count && S->data[index] != elem; index++){}
    for(; index != S->count; index++){
            S->data[index] = S->data[index+1];
    }
    S->count--;
}

boolean isMember(SET S, int elem){
    int index;
    for(index = 0; index < MAX && S.data[index] != elem; index++){}
    return(index < MAX)? 1 : 0;
}

SET UnionSet(SET A, SET B){
    int ctr1, ctr2;
    SET C;
    C.count = 0;
    for(ctr1 = ctr2 = 0; ctr1 < A.count && ctr2 < B.count;){
        if(A.data[ctr1] != B.data[ctr2]){
            C.data[C.count++] = (A.data[ctr1] < B.data[ctr2]) ? A.data[ctr1++] : B.data[ctr2++];
        } else{
            C.data[C.count++] = A.data[ctr1++];
            ctr2++;    
        }
    }
    for(; ctr1 < A.count; ctr1++){
        C.data[C.count++] = A.data[ctr1];
    }
    for(; ctr2 < B.count; ctr2++){
        C.data[C.count++] = B.data[ctr2];
    }
    return C;
}

SET IntersectionSet(SET A, SET B){
    int ctr1, ctr2;
    SET C;
    C.count = 0;
        for(ctr1 = ctr2 = 0; ctr1 <= A.count && ctr2 <= B.count;){
            if(A.data[ctr1] != B.data[ctr2]){
                (A.data[ctr1] < B.data[ctr2]) ? ctr1++ : ctr2++;
            }else{
                C.data[C.count++] = A.data[ctr1++];
                ctr2++;
            }
        }
    return C;
}

SET DifferenceSet(SET A, SET B){
    int ctr1, ctr2;
    SET C;
    C.count = 0;
    for(ctr1 = ctr2 = 0; ctr1 < A.count && ctr2 < B.count;){
        if(A.data[ctr1] != B.data[ctr2]){
            (A.data[ctr1] < B.data[ctr2])? C.data[C.count++] = A.data[ctr1++] : ctr2;
        } else{
            ctr1++;
            ctr2++;
        }
    }
    if(ctr1 < A.count){
        for(;ctr1 < A.count; ctr1++){
            C.data[C.count++] = A.data[ctr1];
        }
    }
    return C;
}
boolean isSubset(SET A, SET B){
    int ctr1, ctr2;
    for(ctr1 = ctr2 = 0; ctr1 < A.count && ctr2 < B.count;){
        (A.data[ctr1] == B.data[ctr2])? ctr1++ : ctr2++;
    }
    return (ctr2 != B.count)? 0 : 1;
}