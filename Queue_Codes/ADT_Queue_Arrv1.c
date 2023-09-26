/*
ADT Queue Array Implementation Version 1
Version 1: List is a structure containing an array and variable count
Note: this is doing circular array
*/

//A. Include files and macro definitions
#include<stdio.h>
#define MAX 8

//B. Data Structure definition
typedef struct{
    char data[MAX];
    int front;
    int rear;
}QUEUE;

//C. Function prototypes
void initQueue(QUEUE *Q);
void enQueue(QUEUE *Q, char elem);
void deQueue(QUEUE *Q);
char isFront(QUEUE Q);
int isEmpty(QUEUE Q);
int isFull(QUEUE Q);
void displayQ(QUEUE Q);

//D. Function main
void main(){
    printf("\n***** INITIALIZATION ***** \n");
    QUEUE Q;
    initQueue(&Q);
    displayQ(Q);
    printf("\n ***** ENQUEUE ELEMENTS ***** \n");
    enQueue(&Q, 'P');
    enQueue(&Q, 'O');
    enQueue(&Q, 'P');
    enQueue(&Q, 'S');
    enQueue(&Q, 'P');
    enQueue(&Q, 'O');
    enQueue(&Q, 'P');
    enQueue(&Q, 'P');
    displayQ(Q);
    printf("Current front: %c\n", isFront(Q));
    printf("Queue is full?: %d\n", isFull(Q));
    printf("\n ***** DEQUEUE ELEMENTS ***** \n");
    deQueue(&Q);
    deQueue(&Q);
    deQueue(&Q);
    deQueue(&Q);
    displayQ(Q);
    deQueue(&Q);
    deQueue(&Q);
    deQueue(&Q);
    deQueue(&Q);
    printf("\n ***** CHECK ELEMS ***** \n");
    printf("Queue is full?: %d\n", isFull(Q));
    printf("Queue is empty after more dequeues?: %d\n", isEmpty(Q));
    
}
//E. Function definitions of the prototypes
void initQueue(QUEUE *Q){
    //circ array: front is ahead of rear by 1
    Q->front = 1;
    Q->rear = 0;
}
void enQueue(QUEUE *Q, char elem){
    if((Q->rear+2) % MAX != Q->front){
        //set rear to next node
        Q->rear = (Q->rear+1)%MAX;
        //set data in the rear to the element to be enqueued
        Q->data[Q->rear] = elem;
    }
}
void deQueue(QUEUE *Q){
    if((Q->rear+1) % MAX != Q->front){
        Q->front = (Q->front+1) % MAX;
    }
}
char isFront(QUEUE Q){
    return((Q.rear+1)%MAX != Q.front)? Q.data[Q.front] : '\0';
}
int isEmpty(QUEUE Q){
    //if front is ahead of rear by 1 cell
    return((Q.rear+1)%MAX == Q.front)? 1 : 0;
}
int isFull(QUEUE Q){
    //if front is ahead of rear by 2 cells
    return((Q.rear+2)%MAX == Q.front)? 1 : 0;
}
void displayQ(QUEUE Q){
    int index;
    if((Q.rear + 1) % MAX != Q.front){
        for(index = Q.front; 
        index != (Q.rear+1) % MAX; 
        index = (index+1) % MAX){
        printf("%c -> ", Q.data[index]);
        }
        printf("NULL\n");
    }else{
        printf("Queue Q is Empty\n");
    }
}