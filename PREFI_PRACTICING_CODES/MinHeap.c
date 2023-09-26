#include<stdio.h>

#define SIZE 15

typedef struct{
    int Elem[SIZE];
    int lastNdx;
}HEAP;

void INITIALIZE(HEAP *H);
void POPUUNSORT(HEAP *H, int arr[], int size);
void DISPLAY(HEAP H);
void INSERTPOT(HEAP * H, int x);
int DELETEMIN(HEAP *H);
void MINHEAPIFY(HEAP *H);
void HEAPSORTMIN(HEAP *H);

void main(){
    /* Initialize*/
    HEAP H;
    INITIALIZE(&H);
    int arr[]={16,8,12,5,7,20};
    int size = sizeof(arr)/sizeof(arr[0]);
    POPUUNSORT(&H,arr,size);
    printf("\n**** UNSORTED LIST ****\n");
    DISPLAY(H);
    /*Heapsort Min*/
    HEAPSORTMIN(&H);
    printf("\n**** HEAP AFTER HEAPSORT ****\n");
    DISPLAY(H);
}
void INITIALIZE(HEAP *H){
    H->lastNdx = -1;
}
void POPUUNSORT(HEAP *H, int arr[], int size){
    int index, childNdx;
    for(index = 0; index < size; index++){
        if(H->lastNdx != SIZE-1){
            H->Elem[childNdx = ++H->lastNdx] = arr[index];
        }
    }
}
void DISPLAY(HEAP H){
    int index;
    for(index  = 0; index < H.lastNdx+1; index++){
        printf("[%d] - %d\n", index, H.Elem[index]);
    }
    printf("\nCurrent LastNdx = %d\n", H.lastNdx);
}
void INSERTPOT(HEAP * H, int x){
    int temp, parentNdx, childNdx;
    if(H->lastNdx != SIZE-1){
        H->Elem[childNdx = ++H->lastNdx] = x;

        while(H->Elem[0] != x && H->Elem[parentNdx = (childNdx-1)/2] > x){
            temp = H->Elem[parentNdx];
            H->Elem[parentNdx] = H->Elem[childNdx];
            H->Elem[childNdx] = temp;
            childNdx = parentNdx;
        }
    }
}
int DELETEMIN(HEAP *H){
    int min = H->Elem[0], parentNdx = 0, childNdx = 1, temp;
    if(H->lastNdx != -1){
        H->Elem[0] = H->Elem[H->lastNdx--];
        while(H->Elem[parentNdx] > H->Elem[childNdx] && childNdx < H->lastNdx){
            temp = H->Elem[parentNdx];
            H->Elem[parentNdx] = H->Elem[childNdx];
            H->Elem[childNdx] = temp;
            parentNdx = childNdx;
            childNdx = parentNdx * 2 + 1;
        }
    }
    return min;
}
void MINHEAPIFY(HEAP *H){
    int temp, childNdx = H->lastNdx, Lparent;
    if(H->lastNdx != -1){ // if heap isnt empty
        Lparent = (H->lastNdx-1)/2; //index of parent of lowest level element

        while(Lparent != -1){
            //find smallest child
            childNdx = ((H->Elem[Lparent*2+1]) < (H->Elem[Lparent*2+2]))? Lparent *2 + 1 : Lparent *2 + 2;
                //check if POT property is satisfied
                if(H->Elem[Lparent] > H->Elem[childNdx] && H->Elem[childNdx] != -1){
                    //swpa
                    temp = H->Elem[Lparent];
                    H->Elem[Lparent] = H->Elem[childNdx];
                    H->Elem[childNdx] = temp;
                    Lparent = childNdx;
                } else {
                    Lparent--; //check other parents
                }
        } 

    }
}
void HEAPSORTMIN(HEAP *H){
    int index, origLNdx, temp;
    origLNdx = H->lastNdx;
    //Method 1 insert all elements to be sorted in an initially empty pot
    H->lastNdx = -1;
    for(index = 0; index <= origLNdx; index++){
        INSERTPOT(H, H->Elem[index]);
    }
    //Method2 Heapify
    //MINHEAPIFY(H);

    //while POT not empty
    while(H->lastNdx != -1){
        temp = DELETEMIN(H);
        H->Elem[H->lastNdx+1] = temp;
    }
    H->lastNdx = origLNdx;
}