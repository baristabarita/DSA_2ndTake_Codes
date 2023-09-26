/*
SET UID Computer Word Implementation
*/
//A. Include files and macro definition
#include <stdio.h>
#define MAX 10

//B. Data Structure definition
typedef unsigned char SET;

//C. Function prototypes
void initSet(SET *S);
void insertSet(SET *S, int elem);
void deleteSet(SET *S, int elem);
int isMember(SET S, int elem);
void displaySet(SET S);
    //UID operations
SET UnionSet(SET A, SET B);
SET IntersectionSet(SET A, SET B);
SET DifferenceSet(SET A, SET B);
SET ComplementSet(SET S);
int isSubset(SET A, SET B);

//D. Function main
void main(){
    SET A, B, C;
    printf("\n***** INITIALIZE *****\n");
    initSet(&A);
    displaySet(A);
    initSet(&B);
    displaySet(B);
    printf("\n\n***** INSERT ELEMENTS TO SET *****\n");
    printf(">> Inserting Set A: \n");
    insertSet(&A, 5);
    insertSet(&A, 3);
    insertSet(&A, 0);
    insertSet(&A, 7);
    displaySet(A);
    printf("\n>> Inserting Set B: \n");
    insertSet(&B, 4);
    insertSet(&B, 3);
    insertSet(&B, 0);
    insertSet(&B, 2);
    insertSet(&B, 1);
    displaySet(B);

    printf("\n\n***** SET UID OPERATION *****\n");
    printf("\n >> Union of Sets A and B: \n");
    C = UnionSet(A,B);
    displaySet(C);
    printf("\n >> Intersection of Sets A and B: \n");
    C = IntersectionSet(A,B);
    displaySet(C);
    printf("\n >> Difference of Sets A and B: \n");
    C = DifferenceSet(A,B);
    displaySet(C);
    printf("\n >> Complement of Set A : \n");
    C = ComplementSet(A);
    displaySet(C);
    

    printf("\n\n***** DELETE ELEMENTS IN SET *****\n");
    printf("\nDeleting in Set A: \n");
    deleteSet(&A, 5);
    displaySet(A);
    printf("\nDeleting in Set B: \n");
    deleteSet(&B, 4);
    displaySet(B);
    printf("\n\n***** CHECK IF MEMBER, ISSUBSET *****\n");
    printf("is 3 a member of set A? : %d\n", isMember(A,3));
    printf("is 5 a member of set B? : %d\n", isMember(B,5));
    printf("Is B a subset of A?: %d", isSubset(A,B));
    
}
//E. Function definitions of the prototypes
void initSet(SET *S){
    *S = 0;
}
void insertSet(SET *S, int elem){
    if(elem < sizeof(*S)*8) //check if elem is within the 8 bit range
    *S |= 1 << elem;
}
void deleteSet(SET *S, int elem){
    if(elem < sizeof(*S)*8)
    *S ^= 1 << elem;
}
int isMember(SET S, int elem){
        //check if elem is within range and is not equal to 0
    return(elem < sizeof(S) * 8) && (S & 1 << elem) != 0 ? 1 : 0;
}
void displaySet(SET S){
    int ndx, size = sizeof(SET)*8;
    for(ndx = 0; ndx < size; ndx++){
        if((S & 1 << ndx) > 0){
            printf("%d ", ndx);
        } else {
            printf("_ ");
        }
    }
}
    //UID operations
SET UnionSet(SET A, SET B){
    return(A | B);
}
SET IntersectionSet(SET A, SET B){
    return (A & B);
}
SET DifferenceSet(SET A, SET B){
    return (A &~ B);
}
SET ComplementSet(SET S){
    return ~S;
}
int isSubset(SET A, SET B){ //note: im not sure about subset still confused about it
    //returns 1/non - zero if Set B is greater than 
    //or equal to Set A  (or that the elements exist AKA not 0), otherwise 0
    return(A & B) ==  0 ? 1 : 0;
}