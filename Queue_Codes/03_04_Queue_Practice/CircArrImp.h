#ifndef CIRCARR_QUEUE
#define CIRCARR_QUEUE

#define MAX 8

#include<stdio.h>
#include<stdlib.h>

typedef struct{
    char elem[MAX];
    int front;
    int rear;
}Queue;

void initQueue(Queue *Q){
    //front is ahead by 1 cell if empty (CLOCKWISE)
    Q->front = 1;
    Q->rear = 0;
}

void displayQ(Queue Q){
    int index;
    if((Q.rear+1) % MAX != Q.front){
        for(index = Q.front; index != (Q.rear+1) % MAX; index = (index+1)%MAX){
            printf("%c -> ", Q.elem[index]);
        }
        printf("NULL\n");
    } else {
        printf("Queue Q is Empty\n");
    }
}
void enQueue(char x, Queue *Q){
    if((Q->rear + 2) % MAX != Q->front){
        //set rear to next node
        Q->rear = (Q->rear + 1) % MAX;
        //assign the elem in rear to elem x
        Q->elem [Q->rear] = x;
    }
}
void deQueue(Queue *Q){
    if((Q->rear + 1) % MAX != Q->front){
        Q->front = (Q->front+1) % MAX;
    }
}

char frontQ(Queue Q){
    return(isEmptyQ(Q) != 1)? Q.elem[Q.front] : '\0';
}
int isEmptyQ(Queue Q){
    return ((Q.rear + 1) % MAX == Q.front) ? 1 : 0;
}
int isFull(Queue Q){
    return ((Q.rear + 2) % MAX == Q.front) ? 1 : 0;
}
#endif