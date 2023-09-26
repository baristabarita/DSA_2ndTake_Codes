#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    char elem;
    struct node *next;
}QNODE;

typedef struct{
    QNODE *front, *rear;
}Queue;

void initQueue(Queue *Q){
    Q->front = NULL;
    Q->rear = NULL;
}

void enQueue(char x, Queue *Q){
    QNODE *temp = (QNODE*)malloc(sizeof(QNODE));
    if(temp!= NULL){
    temp->elem = x;
    temp->next = NULL;

        //if it is first element to be inserted
        if(Q->front == NULL && Q->rear == NULL){
        Q->front = temp;
    } else {
        Q->rear->next = temp; //add newnode in rear->next
    }
    Q->rear = temp; //make the newnode as the new rear
    }
}


void deQueue(Queue *Q){
    QNODE *temp;
    if(Q->front != NULL){ //check if not empty
        temp = Q->front;
        Q->front = Q->front->next;
        free(temp);
    } 
    if(Q->front == NULL){
        Q->rear = NULL;
    }
}

char front(Queue Q){
    return Q.front != NULL ? Q.front->elem : '\0';
}

void displayQueue(Queue Q){
    QNODE *temp = Q.front;
    while(temp){
        printf("%c -> ", temp->elem);
        temp = temp->next;
    }
    printf("NULL\n");
}

void main(){
    Queue Q1;
    initQueue(&Q1);
    enQueue('U',&Q1);
    enQueue('S',&Q1);
    enQueue('C', &Q1);
    displayQueue(Q1);
    printf("Front is %c\n", front(Q1));
    deQueue(&Q1);
    deQueue(&Q1);
    deQueue(&Q1);
    displayQueue(Q1);
}