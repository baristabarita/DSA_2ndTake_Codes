/*
ADT STACK Cursor Based Implementation
*/

//A. Include files and macro definition
#include <stdio.h>
#define MAX 10

//B. Data Structure definition
typedef struct{
    char data;
    int link;
}nodeType;

typedef struct{
    nodeType Nodes[MAX];
    int Avail;
}VirtualHeap;

typedef int CBStack;

//C. Function prototypes
    //Virtual Heap Management Routines
void initVirtualHeap(VirtualHeap *VH);
int allocSpace(VirtualHeap *VH);
void deallocSpace(VirtualHeap *VH, int index);
    //ADT Stack Operations
void initCBStack(CBStack *S);
void push(VirtualHeap *VH, CBStack *S, char elem);
void pop(VirtualHeap *VH, CBStack *S);
char isTop(VirtualHeap VH, CBStack S);
int isEmpty(CBStack S);
int isFull(VirtualHeap VH);
void displayStack(VirtualHeap VH, CBStack S);
//D. Function main
void main(){
    VirtualHeap VH;
    CBStack S;
    printf("\n***** INITIALIZATION *****\n");
    initVirtualHeap(&VH);
    initCBStack(&S);
    displayStack(VH, S);
    printf("\n***** PUSH ELEMENTS *****\n");
    push(&VH, &S, 'L');
    push(&VH, &S, 'L');
    push(&VH, &S, 'Z');
    push(&VH, &S, 'T');
    push(&VH, &S, 'U');
    push(&VH, &S, 'N');
    push(&VH, &S, 'Z');
    push(&VH, &S, 'E');
    push(&VH, &S, 'E');
    push(&VH, &S, 'D');
    displayStack(VH, S);
    printf("\n***** CHECK TOP, ISEMPTY, ISFULL *****\n");
    printf("Current top: %c\n", isTop(VH, S));
    printf("is Full?: %d\n", isFull(VH));
    printf("is Empty?: %d\n", isEmpty(S));
    printf("\n***** POP ELEMENTS *****\n");
    pop(&VH, &S);
    pop(&VH, &S);
    displayStack(VH, S);
    printf("\n***** CHECK TOP, ISEMPTY, ISFULL *****\n");
    printf("Current top: %c\n", isTop(VH, S));
    printf("is Full?: %d\n", isFull(VH));
    pop(&VH, &S);
    pop(&VH, &S);
    pop(&VH, &S);
    pop(&VH, &S);
    pop(&VH, &S);
    pop(&VH, &S);
    pop(&VH, &S);
    pop(&VH, &S);
    printf("\nafter popping all elems, is Empty?: %d\n", isEmpty(S));

}
//E. Function definitions of the prototypes
    //Virtual Heap Management Routines
void initVirtualHeap(VirtualHeap *VH){
    int index;
    VH->Avail = MAX-1; //to hold first available node
    for(index = 0; index < MAX; index++){
        VH->Nodes[index].link = index-1;
    }
}
int allocSpace(VirtualHeap *VH){
    int temp = -1;//initialize to null
    if(VH->Avail != -1){
        temp = VH->Avail;
        VH->Avail = VH->Nodes[temp].link;
    }
    return temp;
}
void deallocSpace(VirtualHeap *VH, int index){
    VH->Nodes[index].link = VH->Avail;
    VH->Avail = index;
}
    //ADT Stack Operations
void initCBStack(CBStack *S){
    (*S) = -1;//set to NULL
}
void push(VirtualHeap *VH, CBStack *S, char elem){
    int temp = allocSpace(VH);
    if(temp != -1){
        VH->Nodes[temp].data = elem;
        VH->Nodes[temp].link = *S;
        *S = temp;
    }
}
void pop(VirtualHeap *VH, CBStack *S){
    int temp;
    if((*S) != -1){
        temp = *S;
        *S = VH->Nodes[temp].link;
        deallocSpace(VH, temp);
    }
}
char isTop(VirtualHeap VH, CBStack S){
    return (S != -1)? VH.Nodes[S].data : '\0';
}
int isEmpty(CBStack S){
    return (S == -1)? 1 : 0;
}
int isFull(VirtualHeap VH){
    return (VH.Avail == -1)? 1 : 0;
}
void displayStack(VirtualHeap VH, CBStack S){
    int trav;
    for(trav = S; trav != -1; trav = VH.Nodes[trav].link){
        printf("%c -> ", VH.Nodes[trav].data);
    }
    printf("NULL\n");
}