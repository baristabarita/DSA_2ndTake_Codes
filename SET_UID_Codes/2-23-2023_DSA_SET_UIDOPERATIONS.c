#include <stdio.h>
#include <stdlib.h>

#define SIZE 5
typedef int SET[SIZE];

SET *unionSet(SET A, SET B);
SET *intersectionSet(SET A, SET B);
SET *differenceSet(SET A, SET B);
void displaySet(SET S);

void main(){
    SET C = {0,1,0,1,1};
    SET D = {1,1,0,1,0};
    displaySet(C);
    printf("\n");
    displaySet(D);
    SET *retval = unionSet(C,D);
    printf("\nUnion of C and D: ");
    displaySet(*retval);
    retval = intersectionSet(C,D);
    printf("\nIntersection of C and D: ");
    displaySet(*retval);
    retval = differenceSet(C,D);
    printf("\nDifference of C and D: ");
    displaySet(*retval);
    retval = differenceSet(D,C);
    printf("\nDifference of D and C: ");
    displaySet(*retval);
}


SET *unionSet(SET A, SET B){
    SET *retval = (SET*)malloc(sizeof(SET));
    int index;

    if(retval != NULL){
        for(index = 0; index < SIZE; index++){
            (*retval)[index] = (A[index] == 1 || B[index]== 1)? 1 : 0;
        }
    }
    return retval;
}
SET *intersectionSet(SET A, SET B){
    SET *retval = (SET*)malloc(sizeof(SET));
    int index;

    if(retval != NULL){
        for(index = 0; index < SIZE; index++){
            (*retval)[index] = (A[index] == 1 && B[index]== 1)? 1 : 0;
        }
    }
    return retval;
}
SET *differenceSet(SET A, SET B){
    SET *retval = (SET*)malloc(sizeof(SET));
    int index;

    if(retval != NULL){
        for(index = 0; index < SIZE; index++){
            (*retval)[index] = (A[index] &&! B[index])? 1 : 0;
        }
    }
    return retval;
}
void displaySet(SET S){
    int index;
    for(index = 0; index < SIZE; index++){
        printf("%d", S[index]);
    }
}
