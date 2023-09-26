/*
SET UID Array Implementation
NOTE: This uses a regular array with index 0 storing the number of active elements
      which are placed beginning from index 1.
*/
//A. Include files and macro definition
#include <stdio.h>
#include <stdlib.h>

#define MAX 20

//B. Data Structure definition
typedef int SET[MAX];
typedef enum{TRUE, FALSE} boolean;

//C. Function prototypes
void initSet(SET S);
void displaySet(SET S);
void insert(SET S, int elem);
void delete(SET S, int elem);
boolean isMember(SET S, int elem);
SET* UnionSet(SET A, SET B);
SET* IntersectionSet(SET A, SET B);
SET* DifferenceSet(SET A, SET B);
boolean isSubset(SET A, SET B);

//D. Function main
void main(){
    SET D,E,*F;
	initSet(D);
	initSet(E);
	int ctr,arr[10] = {1,5,5,7,29,42,60,16,0, 30},arr2[10] = {2,3,5,8,17,13,99,4,24,89};
	for(ctr = 0; ctr < 10; ctr++){
		insert(D,arr[ctr]);
		insert(E,arr2[ctr]);
	}
	displaySet(D);
	displaySet(E);
    printf("\nAFTER SET UNION\n");
    F = UnionSet(D,E);
	displaySet(*F);
    printf("\nAFTER SET INTERSECTION\n");
    F = IntersectionSet(D,E);
    displaySet(*F);
    printf("\nAFTER SET DIFFERENCE\n");
    F = DifferenceSet(D, E);
    displaySet(*F);
}
//E. Function definitions of the prototypes
void initSet(SET S){
    S[0] = 0;
    //index 0 will store the number of active elems
}
void displaySet(SET S){
    int count;
    printf("The number of active elements in the SET is: %d and the values are: {", S[0]);
    if(S[0] != 0){ //if not empty
    //set count to 1, if count is less than the max # of active elems, increment
        for(count = 1; count < S[0]; count++){
            printf("%d, ", S[count]); //display the elem at index count 
        }
        printf("%d", S[count]); //display the elem at index count 
        printf("}\n");
    }
}
void insert(SET S, int elem){
    int count, temp;

    /*set count to one, if count is less than or equal to the # of active elems
    and that the element at index count is less than the new element, traverse and move*/
    for(count = 1; count <= S[0] && S[count] < elem; count++){}
    if(S[0] > 0){ //if not empty
    //if count has not reached max and the element does not exist
        if(count < MAX && elem != S[count]){
            /*set temp to current count and set count to # of active elems + 1 
              if count is greater than temp, decrement count*/
            for(temp = count, count = S[0] + 1; count > temp; count--){
                //assign the element of the previous count index (???) to the current count index
                S[count] = S[count-1];
            }
        }
    }
    //if empty, assign the new element to the first index then increment the # of active elems
    S[count] = elem;
    S[0]++;
}
void delete(SET S, int elem){
    int count;

    /*set count to one, if count is less than or equal to the # of active elems
    and that the element at index count is not equal to the new element, traverse and move count*/
    for(count = 1; count <= S[0] && S[count] != elem; count++){}
    //if count is less than or equal to the # of active elems and that Set is not empty
    if(count <= S[0] && S[0] != 0){
        //Decrement the # of active elems, if count is less than or equal to the number of active elems, increment
        for(S[0]--; count <= S[0]; count++){
            //assign the next element of the next index to the current index
            S[count] = S[count+1];
        }
    }
}
boolean isMember(SET S, int elem){
    int count;
    //set count to first index, if count is less than or equal to # of active elems
    //and that the element at index count is not the elem to be searched, traverse
    for(count = 1; count <= S[0] && S[count] != elem; count++){}
    //is count greater than # of active elems? return False, else return True
    return(count > S[0])? FALSE: TRUE;
}
SET* UnionSet(SET A, SET B){
    int count1, count2;
    SET *C;
    //dynamically allocate new Set C
    C = (SET*)malloc(sizeof(SET));
    if(C != NULL){
        //initialize new Set C
        initSet(*C);
        //set the # of active elements of Set C to the same value of count1 and count2 (1)
        //if count1 and count2 is less than or equal to the # of active elems of Sets A and B respectively
        for((*C)[0] = count2 = count1 = 1;
            count1<= A[0] && count2 <= B[0];){

        //if element of A at index count1 is not the same as the element of B at index count2
        if(A[count1] != B[count2]){
            /*if the element of A is less than the element of B, assign the next element of A to
              the next index of C, else assign then next element of B to the next index of C*/
            (*C)[(*C)[0]++] = A[count1] < B[count2] ? A[count1++] : 
                                                      B[count2++];
        } else {
        //else assign the next element of A to the next index of C and increment count2
            (*C)[(*C)[0]++] = A[count1++];
            count2++;
        }
      }

      //if count1 is less than or equal to # of active elems in set A, increment count
        for(;count1 <= A[0]; count1++){
            //assign the element of A at index count1 to the next index of set C?????
            (*C)[(*C)[0]++] = A[count1];
        }
      //if count2 is less than or equal to # of active elems in set B, increment count
        for(;count2 <= B[0]; count2++){
            //assign the element of B at index count2 to the next index of set C?????
            (*C)[(*C)[0]++] = B[count2];
        }
        //decrement the # of active elements in set C (???)
      (*C)[0]--;
    }
    return C;
}
SET* IntersectionSet(SET A, SET B){
    int count1, count2;
    SET *C;
    //dynamically allocate SET C
    C = (SET*)malloc(sizeof(SET));
    if(C!=NULL){ //if successful allocation
        initSet(*C); //initialize SET C
        //assign the value of the # of active elements in set C and count1 and count2 to 1
        //check if count1 and count2 are less than or equal to the # of active elements in set A and B respectively
        for((*C)[0] = count2 = count1 = 1; count1 <= A[0] && count2 <= B[0];){
            //if element in index count1 of Set A is not equal to element in index count2 of Set B
            if(A[count1] != B[count2]){
            //if the element in set A is less than the element in set B, increment count1, otherwise increment count2
                (A[count1] < B[count2]) ? count1++ : count2++;
            }else{
            //else, set the element of the next count1 index in set A to Set C then increment count2
                (*C)[(*C)[0]++] = A[count1++];
                count2++;
            }
        }
        //decrement the # of active elems?
        (*C)[0]--;
    }
    return C;
}
SET* DifferenceSet(SET A, SET B){
    int count1, count2;
    SET *C;
    //dynamically allocate set C
    C = (SET*)malloc(sizeof(SET));
    if(C != NULL){
        initSet(*C);//initialize set C
        
        //assign the value of the # of active elements in set C and count1 and count2 to 1
        //check if count1 and count2 are less than or equal to the # of active elements in set A and B respectively
        for((*C)[0] = count2 = count1 = 1; count1 <= A[0] && count2 <= B[0];){
        //if element in index count1 of Set A is not equal to element in index count2 of Set B
            if(A[count1] != B[count2]){
                //if the element in set A is less than the element in set B, assign the value of the next 
                //elem to the next node of set C?????, otherwise increment count2
                (A[count1] < B[count2])? (*C)[(*C)[0]++] = A[count1++] : count2++;
            }else{
                //increment both counts
                count1++;
                count2++;
            }
        }
        //if count1 is less than or equal to the # of active elems in set A
        if(count1 <= A[0]){
            //if count1 is less than or equal to the # of active elems in set A, increment count
            for(;count1 <= A[0]; count1++){
                //assign the element at index count1 in set A to the next node of set C
                (*C)[(*C)[0]++] = A[count1];
            }
        }
    }
    (*C)[0]--;
    return C;
}
boolean isSubset(SET A, SET B){
    int count1, count2;
    //set count1 and count2 to 1, check if both counts are less than or equal to the # of active elems in both setsS
    for(count1 = count2 = 1; count1 <= A[0] && count2 <= B[0];){
        //if both elements are equal, increment count1, otherwise increment count2
        (A[count1] == B[count2]) ? count1++ : count2++;
    }
    //is count1 greater than the # of active elems of Set A? return TRUE, else return FALSE
    return(count1 > A[0])? TRUE: FALSE;
}