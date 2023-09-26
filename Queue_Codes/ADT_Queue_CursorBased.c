/*
ADT Queue Cursor Based Implementation
*/
//A. Include files and macro definition
#include <stdio.h>
#define MAX 5

//B. Data Structure definition
typedef struct{
    char data;
    int link;
} nodeType;
typedef struct{
    nodeType Nodes[MAX];
    int Avail;
}VirtualHeap;
typedef struct{
    int front;
    int rear;
}QUEUE;

//C. Function prototypes
    //Virtual Heap Management Routines
void initVirtualHeap(VirtualHeap *VH);
int allocSpace(VirtualHeap *VH);
void deallocSpace(VirtualHeap *VH, int index);
    //ADT Queue Operations
void initQueue(QUEUE *Q);
void enQueue(VirtualHeap *VH, QUEUE *Q, char elem);
void deQueue(VirtualHeap *VH, QUEUE *Q);
char isFront(VirtualHeap VH, QUEUE Q);
int isEmpty(QUEUE Q);
int isFull(VirtualHeap VH);
void displayQ(VirtualHeap VH, QUEUE Q);

//D. Function main
void main(){
    printf("\n***** INITIALIZATION ***** \n");
    VirtualHeap VH;
    QUEUE Q;
    initVirtualHeap(&VH);
    initQueue(&Q);
    displayQ(VH,Q);
    printf("\n ***** ENQUEUE ELEMENTS ***** \n");
    enQueue(&VH, &Q, 'P');
    enQueue(&VH, &Q, 'O');
    enQueue(&VH, &Q, 'P');
    enQueue(&VH, &Q, 'S');
    enQueue(&VH, &Q, 'Z');
    displayQ(VH, Q);
    printf("Current front: %c\n", isFront(VH, Q));
    printf("is Queue full?: %d\n", isFull(VH));
    printf("\n ***** DEQUEUE ELEMENTS ***** \n");
    deQueue(&VH, &Q);
    deQueue(&VH, &Q);
    deQueue(&VH, &Q);
    deQueue(&VH, &Q);
    deQueue(&VH, &Q);
    printf("\n ***** CHECK ELEMS ***** \n");
    printf("is Queue empty?: %d\n", isEmpty(Q));
}
//E. Function definitions of the prototypes
    //Virtual Heap Management Routines
void initVirtualHeap(VirtualHeap *VH){
    int index;
    VH->Avail = MAX - 1; //hold first available node
    for(index = 0; index < MAX; index++){
        VH->Nodes[index].link = index-1;
    }
}
int allocSpace(VirtualHeap *VH){
    int temp = -1; //initialize to NULL
    if(VH->Avail != -1){ //if there is still available nodes
        temp = VH->Avail;//set temp to the available node
        VH->Avail = VH->Nodes[temp].link; //set avail to next available node
    }
    return temp;
}
void deallocSpace(VirtualHeap *VH, int index){
    VH->Nodes[index].link = VH->Avail;
    VH->Avail = index;
}
    //ADT Queue Operations
void initQueue(QUEUE *Q){
    //set both to null
    Q->front = -1;
    Q->rear = -1; 
}
void enQueue(VirtualHeap *VH, QUEUE *Q, char elem){
    int temp = allocSpace(VH);
    if(temp != -1){
        VH->Nodes[temp].data = elem;
        VH->Nodes[temp].link = -1;
        if(Q->front == -1 && Q->rear == -1){
            Q->front = temp;
        } else {
            VH->Nodes[Q->rear].link = temp;
        }
        Q->rear = temp;
    }
}
void deQueue(VirtualHeap *VH, QUEUE *Q){
    int temp = Q->front;
    if(temp != -1){
        Q->front = VH->Nodes[temp].link;
        deallocSpace(VH, temp);
    }
    if(Q->front == -1){
        Q->rear = -1;
    }
}
char isFront(VirtualHeap VH, QUEUE Q){
    return (Q.front != -1)? VH.Nodes[Q.front].data : '\0';
}
int isEmpty(QUEUE Q){
    return (Q.front == -1 && Q.rear == -1)? 1 : 0;
}
int isFull(VirtualHeap VH){
    return (VH.Avail == -1)? 1 : 0;
    //can be return (Q.front==MAX-1 && Q.rear==0)? 1 : 0 if params
    //is QUEUE Q instead
}
void displayQ(VirtualHeap VH, QUEUE Q){
    int index = Q.front;
    while(index != -1){
        printf("%c -> ", VH.Nodes[index].data);
        index = VH.Nodes[index].link;
    }
    printf("NULL\n");
}