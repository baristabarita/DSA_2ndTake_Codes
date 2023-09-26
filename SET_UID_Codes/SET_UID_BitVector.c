/*
SET UID BitVector Implementation
*/
//A. Include files and macro definition
#include <stdio.h>
#include <stdlib.h>
#define MAX 10

//B. Data Structure definition
typedef int SET[MAX];
typedef enum {TRUE, FALSE} boolean;

//C. Function prototypes
void initSet(SET S);
void displaySet(SET S);
void insertSet(SET S, int elem);
void deleteSet(SET S, int elem);
boolean isMember(SET S, int elem);

SET* UnionSet(SET A, SET B);
SET* IntersectionSet(SET A, SET B);
SET* DifferenceSet(SET A, SET B);
SET* ComplementSet(SET A);
boolean isSubset(SET A, SET B);

//D. Function main
void main(){
    SET A, B, *C;
    printf("\n**** INITIALIZATION ****\n");
    initSet(A);
    initSet(B);
    displaySet(A);
    printf("\n");
    displaySet(B);
    printf("\n**** INSERT ELEMENTS ****\n");
    printf("\nSET A ELEMENTS: ");
    insertSet(A, 3);
    insertSet(A, 6);
    insertSet(A, 9);
    displaySet(A);
    printf("\nSET B ELEMENTS: ");
    insertSet(B, 4);
    insertSet(B, 3);
    insertSet(B, 6);
    insertSet(B, 7);
    displaySet(B);
    printf("\n**** SET UNION ****\n");
    printf("\nSET C ELEMENTS IN UNION: ");
    C = UnionSet(A, B);
    displaySet(*C);
    printf("\n**** SET INTERSECTION ****\n");
    printf("\nSET C ELEMENTS IN INTERSECTION: ");
    C = IntersectionSet(A, B);
    displaySet(*C);
    printf("\n**** SET DIFFERENCE ****\n");
    printf("\nSET C ELEMENTS IN DIFFERENCE: ");
    C = DifferenceSet(A, B);
    displaySet(*C);
    printf("\n**** SET COMPLEMENT ****\n");
    printf("\nSET C COMPLEMENT: ");
    C = ComplementSet(A);
    displaySet(*C);
    printf("\n**** SET ISSUBSET ****\n");
    printf("\nIs Set B a subset of A?: %d\n", isSubset(A, B));
    printf("\n**** SET CHECK MEMBERSHIP ****\n");
    printf("\nis 3 a member of A?: %s", isMember(A, 3) == 0? "TRUE" : "FALSE");
    deleteSet(A, 3);
    printf("\nis 3 a member of A?: % s", isMember(A, 3) == 0? "TRUE" : "FALSE");
    
}
//E. Function definitions of the prototypes
void initSet(SET S){
    int ndx;
    for(ndx = 0; ndx < MAX; ndx++){
        S[ndx] = 0;
    }
}
void displaySet(SET S){
    int x;
	for (x = 0; x < MAX; x++){
		printf("\n[%d] %d", x , S[x]);
	}
	printf("\n");
}
void insertSet(SET S, int elem){
    if(elem < MAX){
        S[elem] = 1;
    }
}
void deleteSet(SET S, int elem){
    if(elem < MAX){
        S[elem] = 0;
    }
}
boolean isMember(SET S, int elem){
    return(S[elem] == 1)? TRUE : FALSE;
}

SET* UnionSet(SET A, SET B){
    int index;
    SET *C = (SET*)calloc(MAX, sizeof(SET));
    
    if(C != NULL){
        for(index = 0; index < MAX; index++){
            (*C)[index] = (A[index] == 1 || B[index] == 1)? 1 : 0;
        }
    }
    return C;
}
SET* IntersectionSet(SET A, SET B){
    int index;
    SET *C = (SET*)malloc(sizeof(SET));
    if(C != NULL){
        for(index = 0; index < MAX; index++){
            (*C)[index] = (A[index] == 1 && B[index] == 1)? 1 : 0;
        }
    }
    return C;
}
SET* DifferenceSet(SET A, SET B){
    int index;
    SET *C = (SET*)malloc(sizeof(SET));
    if(C != NULL){
        for(index = 0; index < MAX; index++){
            (*C)[index] = (A[index] &&! B[index])? 1 : 0;
        }
    }
    return C;
}
SET* ComplementSet(SET A){
    int index; 
    SET *C = (SET*)malloc(sizeof(SET));
    if(C != NULL){
        for(index = 0; index < MAX; index++){
            (*C)[index] = !(A[index]);
        }
    }
    return C;
}
boolean isSubset(SET A, SET B){
    int index;
    for(index = 0; index < MAX && (A[index] == 1 ? (B[index] == 1 ? 1 : 0) : 1) ; index++){}
    return (index != MAX)? 0 : 1;
}