// Task A Include Files
#include <stdio.h>
#include <stdlib.h>

typedef enum {FALSE,TRUE} boolean;

//Task B Function Prototypes
int *inputArray();
void displayArray(int arr[], int size);
boolean isMember(int arr[], int size, int x);

//Task C Main Function
void main(){
    int *myArr;
    

    printf("\nTask 1: \n");
    //To call inputArray() and displayArray
    myArr = inputArray();
    displayArray(myArr, myArr[0]);

    printf("\n\nTask 2: \n");
    //To call isMember TWICE
        //1st call -> element is found
    //boolean checkMem = isMember(myArr, myArr[0], 4);

    int checkMem = isMember(myArr, myArr[0], 4);
    printf("\n %d", checkMem);

        //2nd call -> element is not found
    int checkMem2 = isMember(myArr, myArr[0], 9);
    printf("\n %d", checkMem2);
}

//Task D Definition of the functions listed in the
//function prototype
int *inputArray(){
    int N, index;
    int *arr;
    scanf("%d", &N);

    arr = (int*)malloc(sizeof(int)*(N+1));

    if(arr != NULL){ //check if memory allocation was successful
        arr[0] = N;
        for(index = 1; index <= N; index++){
            scanf("%d", &arr[index]);
        }
    }
    return arr;
}

void displayArray(int arr[], int size){
    int index;
    for(index = 1; index <= size; index++){
        printf("%d ", arr[index]);
    }
}

boolean isMember(int arr[], int size, int x){
    boolean check;
    int index;
    for(index = 1; index < size && arr[index] != x; index++){
        return (index == size)? FALSE:TRUE;
    }
}