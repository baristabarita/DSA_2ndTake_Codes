/* HeapSort in Descending order*/
#include<stdio.h>

#define SIZE 15

typedef struct{
    int Elem[SIZE];
    int lastNdx;
}HEAP;

void initialize(HEAP *H);
void insertPOT(HEAP *H, int x);
void popuUnsort(HEAP *H, int arr[], int size);
int deleteMin(HEAP *H);
void HeapSortMin(HEAP *H);
void MinHeapify(HEAP *H);
void display(HEAP H);

void main(){
    /* Initialize */
    HEAP H;
    initialize(&H);
    /* Populate */
    int arr[]={16,8,12,4,7,20};
    int size = sizeof(arr)/sizeof(arr[0]);
    popuUnsort(&H,arr,size);
    printf("\n**** UNSORTED LIST ****\n");
    display(H);
    /* Heapsort Min */
    HeapSortMin(&H);
    printf("\n**** HEAP AFTER HEAPSORT ****\n");
    display(H);
}

void initialize(HEAP *H){
    H->lastNdx = -1;
}
void display(HEAP H){
    int index;
    for(index = 0; index < H.lastNdx+1; index++){
        printf("[%d] - %d\n", index, H.Elem[index]);
    }
    printf("\nCurrent LastNdx = %d\n", H.lastNdx);
}
void popuUnsort(HEAP *H, int arr[], int size){
    int index, childNdx;
    for(index = 0; index < size; index++){
        if(H->lastNdx != SIZE-1){
            H->Elem[childNdx = ++H->lastNdx] = arr[index];
        }
    }
}
void insertPOT(HEAP *H, int x){
    int temp, parentNdx, childNdx;
    //check for available space
    if(H->lastNdx != SIZE-1){
        //place new elem x at lowest level to the right of the leaves present or to the next level
        H->Elem[childNdx = ++H->lastNdx] = x;

        //while elem x is not root and POT property is not satisfied
        while(H->Elem[0] != x && H->Elem[parentNdx = (childNdx-1)/2] > x){
            //SWAP
            temp = H->Elem[parentNdx];
            H->Elem[parentNdx] = H->Elem[childNdx];
            H->Elem[childNdx] = temp;
            childNdx = parentNdx;
        }
    }
}
int deleteMin(HEAP *H){
    int min = -1, parNdx, childNdx, temp;

    if(H->lastNdx != -1){
        min = H->Elem[0];
        H->Elem[0] = H->Elem[H->lastNdx];
        --H->lastNdx;
        parNdx = 0;
        childNdx = 1; 
        //check if a child does exist
        while(childNdx <= H->lastNdx){
            if(childNdx <= H->lastNdx && H->Elem[childNdx+1] < H->Elem[childNdx]){
                childNdx++;
            }
            //if POT unsatisfied
            if(H->Elem[parNdx] > H->Elem[childNdx]){
                temp = H->Elem[parNdx];
                H->Elem[parNdx] = H->Elem[childNdx];
                H->Elem[childNdx] = temp;
                parNdx = childNdx;
                childNdx = (2*parNdx)+1;
            }
        }
    }
    return min;
}
void MinHeapify(HEAP *H){
    int lowestLvlPar, parNdx, childNdx, temp;

    //check if not empty
    if(H->lastNdx != -1){
        //determine lowest level parent
        lowestLvlPar = (H->lastNdx-1)/2;
        while(lowestLvlPar >= 0){
            parNdx = lowestLvlPar;
            childNdx = (2*parNdx)+1;

            //if the RC index is less than or equal to the lastNdx and is less than LC
            if(childNdx+1 <= H->lastNdx && H->Elem[childNdx+1] < H->Elem[childNdx]){
                //increment childNdx;
                childNdx++;
            }
            //check POT property
            if(H->Elem[parNdx] > H->Elem[childNdx]){
                //SWAP if unsatisfied POT
                temp = H->Elem[parNdx];
                H->Elem[parNdx] = H->Elem[childNdx];
                H->Elem[childNdx] = temp;
                parNdx = childNdx;
                childNdx = (2*parNdx)+1;
            } else {
                break;
            }
        }
        --lowestLvlPar;
    }
}
//can switch between insert through initially empty POT or heapifyMin
void HeapSortMin(HEAP *H){
    int index, origLastNDX, temp;
    origLastNDX = H->lastNdx;
    
    /*
    //METHOD 1: Insert all elements to be sorted in an initially empty POT
    H->lastNdx = -1; //to make it look logically initially empty
    for(index = 0; index <= origLastNDX; index++){
        insertPOT(H, H->Elem[index]);
    }*/
    
    //METHOD2: HEAPIFY
    MinHeapify(H);

    //while POT not empty
    while(H->lastNdx != -1){
        //deleteMin and store the deleted min elem in the pos of the element
        //which will replace the root
        temp = deleteMin(H);
        H->Elem[H->lastNdx+1] = temp;
    }
    H->lastNdx = origLastNDX;
}