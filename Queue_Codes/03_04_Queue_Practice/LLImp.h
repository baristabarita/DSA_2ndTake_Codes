#ifndef LL_QUEUE
#define LL_QUEUE

#include <stdio.h>
#include <stdlib.h>

//Using Version B of singly linked ver 2
typedef struct node{
    char elem;
    struct node *next;
}Qtype, *QNODE;
typedef struct{
    QNODE front, rear;
}Queue;

void initQueue(Queue *Q){
    Q->front = NULL;
    Q->rear = NULL;
}

void displayQ(Queue Q){
    QNODE trav = Q.front;
    while(trav){
        printf("%c -> ", trav->elem);
        trav = trav->next;
    }
    printf("NULL\n");
}

void enQueue(char x, Queue *Q){
    QNODE temp = (QNODE)malloc(sizeof(Qtype));
    if(temp != NULL){
        temp->elem = x;
        temp->next = NULL;
    }
    // if the queue is empty, set front to new elem, else set the next of current rear to temp
    if(Q->front == NULL && Q->rear == NULL){ 
        Q->front = temp;
    } else {
        Q->rear->next = temp;
    }
    // make the new node as the new rear
    Q->rear = temp;
}

void deQueue(Queue *Q){
    QNODE temp = Q->front;
    if(temp != NULL){
        Q->front = temp->next;
        free(temp);
    }
    // if front is null, set rear to null
    if(Q->front == NULL){
        Q->rear = NULL;
    }
}

char frontQ(Queue Q){
    return(Q.front != NULL)? Q.front->elem : '\0';
}
int isEmptyQ(Queue Q){
    return (Q.front == NULL && Q.rear == NULL)? 1 : 0;
}

#endif