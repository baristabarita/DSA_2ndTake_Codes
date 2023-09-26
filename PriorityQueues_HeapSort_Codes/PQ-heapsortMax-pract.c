/* HeapSort in Ascending Order */

#include <stdio.h>

#define SIZE 15

typedef struct{
    int Elem[SIZE];
    int lastNdx;
}HEAP;

void initialize(HEAP *H);
void popUnsort(HEAP *H, int arr[], int size);
void insertPOT(HEAP *H, int x);
int deleteMax(HEAP *H);
void MaxHeapify(HEAP *H);
void HeapSortMax(HEAP *H);
void display(HEAP H);

void main(){
    /* Initialize */
    HEAP H;
    initialize(&H);
    /* Populate */
    int arr[]={16,8,12,4,7,20};
    int size=sizeof(arr)/sizeof(arr[0]);
    popUnsort(&H, arr, size);
    printf("\n**** UNSORTED LIST ****\n");
    display(H);
    /* Heapsort Max */
    HeapSortMax(&H);
    printf("\n**** HEAP AFTER HEAPSORT ****\n");
    display(H);
    
}
void initialize(HEAP *H){
    H->lastNdx = -1;
}
void popUnsort(HEAP *H, int arr[], int size){
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
        //place new elem x at lowest level to the right
        //of the leaves present or to the next level
        H->Elem[childNdx = ++H->lastNdx] = x;

        //while elem x is not root and POT property unsatisfied (parent < x)
        while(H->Elem[0] != x && H->Elem[parentNdx = (childNdx-1)/2] < x){
            //SWAP the elements in the parent index and child index
            temp = H->Elem[parentNdx];
            H->Elem[parentNdx] = H->Elem[childNdx];
            H->Elem[childNdx] = temp;
            //set the new child index to the current parent index
            childNdx = parentNdx;
        }
    }
}
int deleteMax(HEAP *H){
    int max = -1, parNdx, childNdx, temp;

    if(H->lastNdx != -1){
        //set the min to the root element
        max = H->Elem[0];
        //let the new root element be the last element
        H->Elem[0] = H->Elem[H->lastNdx];
        //decrement the last index
        --H->lastNdx;
        parNdx = 0;
        //we have a child for as long as there is a child then there is a child to check on
        childNdx = 1;
         //here check if a child does exist, to make sure it is not a leaf
        while(childNdx <= H->lastNdx){
            if(childNdx <= H->lastNdx && H->Elem[childNdx+1] > H->Elem[childNdx]){
                childNdx++;
            }
            //we check if the POT property is unsatisfied.
            //the POT property of max heap is parentndx >= childNdx
            if(H->Elem[parNdx] < H->Elem[childNdx]){
                temp = H->Elem[parNdx];
                H->Elem[parNdx] = H->Elem[childNdx];
                H->Elem[childNdx] = temp;
                parNdx = childNdx;
                childNdx = (2*parNdx)+1;
            }
        }
    }
    return max;
}
void MaxHeapify(HEAP *H){
    int index;
    //set the index to the lowest level parent; check if it exists, then update
    for (index = (H->lastNdx - 1) / 2; index >= 0; index--) {
        //set the biggest variable to the current index
        int biggest = index;
        //compute the left and right children
        int leftNdx = 2 * index + 1;
        int rightNdx = 2 * index + 2;
        //have a ctr variable to stop the loop once POT property is satisfied
        int ctr = 0;
        //check if ctr has not incremented and that he left and right children exists
        while (ctr == 0 && (leftNdx <= H->lastNdx || rightNdx <= H->lastNdx)) {
            //we check if a left child exists and its value is bigger than the current biggest val
            if (leftNdx <= H->lastNdx && H->Elem[leftNdx] > H->Elem[biggest]) {
                biggest = leftNdx;
            }//we check if a right child exists and its value is bigger than the current biggest val
            if (rightNdx <= H->lastNdx && H->Elem[rightNdx] > H->Elem[biggest]) {
                biggest = rightNdx;
            }
        //if biggest is not equivalent to index, then it means that one of the children
        //has a bigger value than the current node
            if (biggest != index) {
                //initiate the swapping
                int temp = H->Elem[index];
                H->Elem[index] = H->Elem[biggest];
                H->Elem[biggest] = temp;
                index = biggest;
                leftNdx = 2 * index + 1;
                rightNdx = 2 * index + 2;
            } else { //if the biggest == index, means the current node is already the biggest value
                ctr = 1; //we increment the counter to stop the loop
            }
        }
    }
}

void HeapSortMax(HEAP *H){
    int index, origLastNdx, temp;
    //set the original last index as the current last index
     origLastNdx = H->lastNdx;
    
    /*
    //METHOD 1: Insert all elements to be sorted in an initially empty POT
    //To make it look lofically initially empty, set last index to empty
    H->lastNdx = -1;
    for(index = 0; index <= origLastNdx; index++){
        insertPOT(H, H->Elem[index]);
    }
    */

    //METHOD 2: MAX HEAPIFY
    MaxHeapify(H);   
    
    
    //while POT is not empty
    
    while(H->lastNdx != -1){
        //deleteMax and store the deleted max elem in the pos of the elem
        //which will replace the root
        temp = deleteMax(H);
        H->Elem[H->lastNdx+1] = temp;
   }
   //after while loop is executed, retain the real last index
   H->lastNdx = origLastNdx;
}

void display(HEAP H){
    int index;
    for(index = 0; index < H.lastNdx+1; index++){
        printf("[%d] - %d\n", index, H.Elem[index]);
    }
    printf("\nCurrent LastNdx = %d\n", H.lastNdx);
}

//maan pena id like to bargain