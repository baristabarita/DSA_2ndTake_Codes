#include <stdio.h>
#include <stdlib.h>
//#include "LLImp.h"
//#include "CircArrImp.h"
#include "CBImp.h"

void main(){
    /*
    Queue Q;
    initQueue(&Q);
    //Array / LL Version
    printf("\nQueue Q initialization: \n");
    displayQ(Q);

    printf("\nQueue Q after Enqueue: \n");
    enQueue('P', &Q);
    enQueue('O', &Q);
    enQueue('G', &Q);
    displayQ(Q);

    printf("Current Queue Q Front: %c\n", frontQ(Q));
    printf("\nQueue Q after Dequeue: \n");
    deQueue(&Q);
    displayQ(Q);
    deQueue(&Q);
    displayQ(Q);

    printf("Current Queue Q Front: %c\n", frontQ(Q));
    printf("\nEmpty Queue Q?: %d", isEmptyQ(Q));
    deQueue(&Q);
    printf("\nEmpty Queue Q after Deque?: %d", isEmptyQ(Q));
    */
    //Cursor Based Version
    Queue Q;
    initQueue(&Q);
    VirtualHeap VH;
    initVirtualHeap(&VH);

    printf("\nQueue Q initialization: \n");
    displayQ(VH, Q);

    printf("\nQueue Q after Enqueue: \n");
    enQueue(&VH, &Q, 'P');
    enQueue(&VH, &Q, 'O');
    enQueue(&VH, &Q, 'G');
    displayQ(VH, Q);
    deQueue(&VH, &Q);
    displayQ(VH, Q);
    deQueue(&VH, &Q);
    displayQ(VH, Q);
}