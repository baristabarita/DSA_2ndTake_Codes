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
    
    //check if available space
    if(H->lastNdx != SIZE-1){
        //place new elem x at lowest level to the right of the leaves present or to the next level
         H->Elem[childNdx = ++H->lastNdx] = x;

        //while elem x is not root and POT property is not satisfied (parent > elem x)
         while(H->Elem[0] != x && 
         H->Elem[parentNdx = (childNdx-1)/2] > x){
            //SWAP
            temp = H->Elem[parentNdx];
            H->Elem[parentNdx] = H->Elem[childNdx];
            H->Elem[childNdx] = temp;
            childNdx = parentNdx;
         }
    }
}
int deleteMin(HEAP *H){
    int min = H->Elem[0], parent = 0, child = 1, temp;
    if(H->lastNdx != -1){
        H->Elem[0] = H->Elem[H->lastNdx--];
        while(H->Elem[parent] > H->Elem[child] && child < H->lastNdx){
            temp = H->Elem[parent];
            H->Elem[parent] = H->Elem[child];
            H->Elem[child] = temp;
            parent = child;
            child = parent * 2 + 1;
        }
    }
    return min;
}
//brute forced this shit
void MinHeapify(HEAP *H){
                                          
    int leftNdx, rightNdx, smallest, temp, index = 0;

          //check if the index is set to the lowest level parent
    while(index <= H->lastNdx / 2){
        //calculate the left and right children of the index
        leftNdx = 2 * index + 1;
        rightNdx = 2 * index + 2;
        //smallest holds index which is the currentt node in the heap/list
        smallest = index;

        //we check if a left child exists and its value is smaller than the current smallest val
        if(leftNdx <= H->lastNdx && H->Elem[leftNdx] < H->Elem[smallest]){
            //if so, update the smallest to the index of the left child.
            smallest = leftNdx;
        }
        //we check if a right child exists and its value is smaller than the current smallest val
        if(rightNdx <= H->lastNdx && H->Elem[rightNdx] < H->Elem[smallest]){
            //if so, update the smallest to the index of the right child
            smallest = rightNdx;
        }
        //if smallest is not equivalent to index, then it means that one of the children
        //has a smaller value than the current node
        if(smallest != index){
            //initiate the swapping
            temp = H->Elem[index];
            H->Elem[index] = H->Elem[smallest];
            H->Elem[smallest] = temp;
            index = smallest;
        } else{ //if smallest == index, means the current node is already the smallest value
            index++; //update index to the index of the next parent node
        }
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
    }
    */

    //METHOD2: HEAPIFY
    MinHeapify(H);
    
    //while POT not empty
    while(H->lastNdx != -1){
        //deleteMin and store the deleted min elem in the pos of the element
        //which will replace the root
        temp = deleteMin(H);
        H->Elem[H->lastNdx+1] = temp;
    }
    
    //after while loop is executed, retain the real last index
    H->lastNdx = origLastNDX;
}

//kabuangon ko tabang