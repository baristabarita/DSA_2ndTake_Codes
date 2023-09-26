#include <stdio.h>
#include <stdlib.h>

//Data Structure Definitions
#define MAX 10

typedef struct{
    char elem[MAX];
    int count;
} LIST;

typedef int Position;

//Function Prototypes
void initList(LIST *L);
void insertPos(LIST *L, char data, Position pos);
void deleteElem(LIST *L, char data);

//Main
void main(){
    //printf("Check");
    LIST *A;
    initList(A);
    insertPos(A, 'U', 1);
    insertPos(A, 'S', 2);
    insertPos(A, '3', 3);
    
    
}

//Function Definitions
void initList(LIST *L){
    L->count = 0;
}
//Given the list, element, and position, write the code of the function insert()
//if there is space and position is valid
void insertPos(LIST *L, char data, Position pos){
    Position index;
    //Check if there is space
    if(L != NULL && L->count < MAX){

        for(index = pos-1; index < pos; index--){
            //Make Room for new element (shifting)
            L->elem[index+1] = L->elem[index-1];
        }
        //insert the new element and update count
        L->elem[pos] = data; 
        L->count++;
    }
}

/* Given the list and element, write the code of the function that will delete
   the element from the list and will update count
*/
void deleteElem(LIST *L, char data){
    int index, trav;

    //check if list is empty
    if(L->count != 0){ 
    //traverse the list and look for element
        for(trav - 0; trav < L->count && L->elem[trav] != data; trav++){}
        //If trav is not equal to count, proceed. if not, element not found
        if(trav != L->count){
            //what the fuck is happening here i dont understand
            for(index = trav; index < L->count-1; index++){
                L->elem[index] = L->elem[index+1];
                }
            } else {
                printf("Element not found");
            }
            //update count
            L->count--;
    }
}