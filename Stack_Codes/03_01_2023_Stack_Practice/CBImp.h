#ifndef CB_STACK
#define CB_STACK
#include<stdio.h>
#define MAX 5

typedef struct{
    char data;
    int link;
}nodeType;

typedef struct{
    nodeType Nodes[MAX];
    int Avail;
}VirtualHeap;

typedef int CBStack;

//Virtual Heap Management Routines
void initVirtualHeap(VirtualHeap *VH){ //uses Version 2
    int index;
    VH->Avail = MAX-1;//Avail holds first available node
    for(index = 0; index < MAX; index++){
        VH->Nodes[index].link = index - 1;
    }
}
int allocSpace(VirtualHeap *VH){
    int temp = -1; //initialize temp to -1, NULL equivalent
    if(VH->Avail != -1){ //if there are still available nodes
        temp = VH->Avail; //set temp to the available node
        VH->Avail = VH->Nodes[temp].link; //set avail to the next available node
    }
    return temp;
}
void deallocSpace(VirtualHeap *VH, int index){
    VH->Nodes[index].link = VH->Avail;
    VH->Avail = index;
}

//Cursor Based Stack Functions
void initStack(CBStack *S){
    (*S) = -1; //set as NULL equiv
}
void displayCBStack(VirtualHeap VH, CBStack S){
    CBStack trav;
    for(trav = S; trav != -1; trav = VH.Nodes[trav].link){
        printf("%c -> ", VH.Nodes[trav].data);
    }
    printf("NULL");
}
void pushCBStack(VirtualHeap *VH, CBStack *S, char elem){
    int temp = allocSpace(VH);
    if(temp != -1){
        VH->Nodes[temp].data = elem;
        VH->Nodes[temp].link = *S;
        *S = temp;
    }

}
void popCBStack(VirtualHeap *VH, CBStack *S){
    int temp;
    if(*S != -1){
        temp = *S;
        *S = VH->Nodes[temp].link;
        deallocSpace(VH, temp);
    }
}
char topCBStack(VirtualHeap VH, CBStack S){
    return (S != -1)? VH.Nodes[S].data : '\0';
}
int isEmptyCBStack(VirtualHeap VH, CBStack S){
    return (S == -1)? 1 : 0;
}
int isFullCBStack(VirtualHeap VH, CBStack S){
    return (S == MAX)? 1 : 0;
    }
#endif