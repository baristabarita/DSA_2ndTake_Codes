#include<stdio.h>
#include<stdlib.h>

//Max Heap Definition
#define MAX 0XD
typedef int maxHeap[MAX];

void initHeap(maxHeap *H);
void insertHeap(maxHeap heap, int elem);

void main(){
    maxHeap H;
    initHeap(&H);
    printf("\nCurrent # of elems: %d\n", (H[0]));
    insertHeap(H, 16);
    insertHeap(H, 8);
    insertHeap(H, 12);
    insertHeap(H, 4);
    insertHeap(H, 7);
    insertHeap(H, 20);
    int index;
    printf("Elements after insertHeap: ");
    for(index = 1; index <= H[0]; index++){
        printf("%d ", H[index]);
    }
}

void initHeap(maxHeap *H){
    *H[0] = 0;
}

//first position of the array contains the # of elems in the maxheap
//inserts a given element by shifting instead of swapping

void insertHeap(maxHeap heap, int elem){
    int index;
    //first increment the element count
    int elem_count = heap[0] + 1;
    //set the first index of the array as the element count
    heap[0] = elem_count;
    /* -- shifting process -- */
    //set the index as the current element count (which is the last index)
    //check if the index is not the root
    // and check if the element to be inserted is bigger than its parent (at index/2)
    // move the index to its parent index (index = index/2)
    for (index = elem_count; index > 1 && elem > heap[index/2]; index /= 2) {
        //we shift the element by placing the parent element to the current index
        heap[index] = heap[index/2];
    }
    //once the for loop has ended and found an appropriate position
    //insert the element
    heap[index] = elem;
}

