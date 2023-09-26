#include<stdio.h>
#include<stdlib.h>
//#include"arrayImp.h"
//#include"LLImp.h"
#include"CBImp.h"

void main(){
    VirtualHeap VH;
    CBStack S;
    initVirtualHeap(&VH);
    initStack(&S);

    printf("Initialized Stack: \n");
    //display(S);
    displayCBStack(VH, S);
    printf("\nStack after Pushing Elements: \n");
    /*
    push('P', &S);
    push('O', &S);
    push('G', &S);
    push('S', &S);
    display(S);
    */
    pushCBStack(&VH, &S, 'O');
    pushCBStack(&VH, &S, 'G');
    pushCBStack(&VH, &S, 'G');
    pushCBStack(&VH, &S, 'O');
    pushCBStack(&VH, &S, 'P');
    displayCBStack(VH, S);
    printf("\nCBStack Full?: %d", isFullCBStack(VH,S));

    printf("\nStack After Pop:\n");
    /*
    pop(&S);
    display(S);
    */
    popCBStack(&VH, &S);
    displayCBStack(VH, S);
    
    //printf("\nCurrent top: %c", top(S));
    printf("\nCurrent CBStack top: %c", topCBStack(VH, S));
    //int check = isEmpty(S);
    //printf("\nStack Empty ?: %d\n", check);
    printf("\nCBStack Empty?: %d", isEmptyCBStack(VH, S));
    //check = isFull(S);
    //printf("\nStack Full?: %d\n", check);
    printf("\nCBStack Full?: %d", isFullCBStack(VH,S));
}