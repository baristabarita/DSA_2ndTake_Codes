#ifndef CB_QUEUE
#define CB_QUEUE

#define MAX 8

typedef struct
{
    char elem;
    int link;
} nodeType;

typedef struct
{
    nodeType Nodes[MAX];
    int Avail;
} VirtualHeap;

typedef struct
{
    int front;
    int rear;
} Queue;

// Virtual Heap Management Routines
void initVirtualHeap(VirtualHeap *VH)
{ // uses Ver 2
    int index;
    VH->Avail = MAX - 1; // Avail holds first available node
    for (index = 0; index < MAX; index++)
    {
        VH->Nodes[index].link = index - 1;
    }
}
int allocSpace(VirtualHeap *VH)
{
    int temp = -1; // initialize temp to -1 (NULL)
    if (VH->Avail != -1)
    {                                     // if there are still available nodes
        temp = VH->Avail;                 // set temp to the available node
        VH->Avail = VH->Nodes[temp].link; // set avail to next available node
    }
    return temp;
}
void deallocSpace(VirtualHeap *VH, int index)
{
    VH->Nodes[index].link = VH->Avail;
    VH->Avail = index;
}

// Queue Operations Functions
void initQueue(Queue *Q)
{
    // set front and rear to null
    Q->front = -1;
    Q->rear = -1;
}

void displayQ(VirtualHeap VH, Queue Q)
{
    int index = Q.front;
    while(index != -1){
        printf("%c -> ", VH.Nodes[index].elem);
        index = VH.Nodes[index].link;
    }
    printf("NULL\n");
}

void enQueue(VirtualHeap *VH, Queue *Q, char x)
{
    int temp = allocSpace(VH);
    if (temp != -1)
    {
        VH->Nodes[temp].elem = x;
        VH->Nodes[temp].link = -1;
        if (Q->front == -1 && Q->rear == -1)
        {
            Q->front = temp;
        }
        else{
            VH->Nodes[Q->rear].link = temp;
        }
            Q->rear = temp;
    }
}

void deQueue(VirtualHeap *VH, Queue *Q)
{
    int temp = Q->front;
    if (temp != -1)
    {
        Q->front = VH->Nodes[temp].link;
        deallocSpace(VH, temp);
    }
    if (Q->front == -1)
    {
        Q->rear = -1;
    }
}

char frontQ(VirtualHeap VH, Queue Q){
    return(Q.front != -1)? VH.Nodes[Q.front].elem: '\0';
}
int isEmptyQ(Queue Q){
    return(Q.front == -1 && Q.rear == -1)? 1: 0;
}
//not sure about isFull
int isFull(Queue Q){
    return(Q.front == MAX-1 && Q.rear == MAX-1)? 1: 0;
}
#endif