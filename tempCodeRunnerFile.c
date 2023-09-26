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
    temp->elem = x;
    temp->next = NULL;

    //if it is first element to be inserted
    if(Q->front == NULL && Q->rear == NULL){
        Q->front = temp;
        Q->rear = temp;
    } else {
        temp->next = Q->rear; //add newnode in rear->next
 //make the newnode as the new rear
    }
    Q->rear = temp;
}

void deQueue(Queue *Q){
    Queue *temp;
    if(Q->front != NULL){ //check if not empty
        temp = Q->front;
        Q->front = Q->front->next;
        free(temp);
    } else{
        Q->rear = NULL;
    }
}

void displayQueue(Queue Q){
    Queue *temp = Q.front;
    while(temp){
        printf("%d -> ", temp->front->elem);
        temp = temp->front->next;
    }
    printf("NULL\n");
}
void main(){
    Queue Q1;
    initQueue(&Q1);
    enQueue('U',&Q1);
    enQueue('S',&Q1);
    enQueue('S', &Q1);
    displayQueue(Q1);

}