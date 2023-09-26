//Partially Ordered Tree Implementation

#include<stdio.h>
#include<stdlib.h>

#define SIZE 15

typedef struct{
    int Elem[SIZE];
    int lastNdx;
}HEAP;

void initialize(HEAP *H);
void insert(HEAP *H, int x);
void populate(HEAP *H, int arr[], int setSize);
int deleteMin(HEAP *H);

void main(){
    HEAP H;
    int set[]={3,5,9,8,6,9,10,10,18,9,4};
    int size = sizeof(set)/sizeof(set[0]);
    initialize(&H);
    populate(&H, set, size);
    printf("%d", deleteMin(&H));
}

void initialize(HEAP *H){
    H->lastNdx = -1;
}


void insert(HEAP *H, int x){
    int temp, parentNdx, childNdx;
    
    //check if available space
    if(H->lastNdx != SIZE-1){
        //place new elem x at lowest level to the right of the leaves present or to the next level
         H->Elem[childNdx = ++H->lastNdx] = x;

        //while elem x is not root and POT property is not satisfied (parent > elem x)
         while(H->Elem[0] != x && H->Elem[parentNdx = (childNdx-1)/2] > x){
            //SWAP
            temp = H->Elem[parentNdx];
            H->Elem[parentNdx] = H->Elem[childNdx];
            H->Elem[childNdx] = temp;
            childNdx = parentNdx;
         }
    }
}
void populate(HEAP *H, int arr[], int setSize){
	    int index;
	    for(index = 0; index < setSize; index++){
	        insert(H, arr[index]);
	    }
	    //H->lastNdx -=1;
}
/*
int deleteMin(HEAP *h){
    int min = h->Elem[0];
    int i = 0;
    int SChild, LCNdx, RCNdx;
    int x = h->Elem[h->lastNdx];
    
    h->Elem[i] = x;

    LCNdx = (i*2)+1;
    RCNdx = (i*2)+2;

    while(h->Elem[i] > h->Elem[LCNdx] || h->Elem[i] > h->Elem[RCNdx]){
        if(LCNdx >= h->lastNdx){
            break; //tentative, idk how to break
        }
        if(h->Elem[LCNdx] < h->Elem[RCNdx]){
            SChild = h->Elem[LCNdx];
            h->Elem[i] = SChild;
            i = LCNdx;
        }else{
            SChild = h->Elem[RCNdx];
            h->Elem[i] = SChild;
            i = RCNdx;   
        }
         h->Elem[i] = x;
    }
    h->Elem[h->lastNdx] = min;
    h->lastNdx -= 1;
    return min;
}*/

int deleteMin(HEAP *H){
    int min = -1, index, child, temp;

    if(H->lastNdx != -1){
        min = H->Elem[0];
        H->Elem[0] = H->Elem[H->lastNdx];
        --H->lastNdx;
        index = 0;
        child = 1; //this is to check if a child does exist (not a leaf)

        while(child <= H->lastNdx){
            //just checking child
            if(child <= H->lastNdx && H->Elem[child+1] < H->Elem[child]){
                child++;
            }
            //if POT unsatisfied
            if(H->Elem[index] > H->Elem[child]){
                temp = H->Elem[index];
                H->Elem[index] = H->Elem[child];
                H->Elem[child] = temp;
                index = child;
                child = index*2+1;
            }
        }
    }   
    return min;
}
int deleteMax(HEAP *H){

}