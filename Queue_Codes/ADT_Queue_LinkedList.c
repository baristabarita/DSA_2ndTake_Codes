/*
ADT Queue Linked List Implementation
    
Note: Uses Version A of Singly Linked List Ver 2
      where front points to the first node and rear points
      to the last node
*/

//A. Include files and macro definition
#include <stdio.h>
#include <stdlib.h>

//B. Data Structure definition
typedef struct node{
    char data;
    struct node *next;
}Qtype, *QNode;

typedef struct{
    QNode front, rear;
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
    displayQ(Q);
    printf("Current front: %c\n", isFront(Q));
    printf("\n ***** DEQUEUE ELEMENTS ***** \n");
    deQueue(&Q);
    deQueue(&Q);
    displayQ(Q);
    printf("\n ***** CHECK ELEMS ***** \n");
    deQueue(&Q);
    deQueue(&Q);
    printf("Is empty after dequeues?: %d", isEmpty(Q));

}
//E. Function definitions of the prototypes
void initQueue(QUEUE *Q){
    Q->front = NULL;
    Q->rear = NULL;
}
void enQueue(QUEUE *Q, char elem){
    QNode temp = (QNode)malloc(sizeof(Qtype));
    if(temp!=NULL){
        temp->data = elem;
        temp->next = NULL;
    }
    /*if the queue is empty, set front to new elem,
       else set the next of current rear to temp*/
    if(Q->front == NULL && Q->rear == NULL){
        Q->front = temp;
    } else {
        Q->rear->next = temp;
    }
    //make the new node as the new rear
    Q->rear = temp;
}
void deQueue(QUEUE *Q){
    QNode temp = Q->front;
    if(temp!= NULL){
        Q->front = temp->next;
        free(temp);
    }
    //if front is NULL, set rear to NULL
    if(Q->front == NULL){
        Q->rear = NULL;
    }
}
char isFront(QUEUE Q){
    return (Q.front != NULL)? Q.front->data : '\0';
}
int isEmpty(QUEUE Q){
    return (Q.front == NULL && Q.rear == NULL)? 1 : 0;
}
void displayQ(QUEUE Q){
    QNode trav = Q.front;
    while(trav){
        printf("%c -> ",trav->data);
        trav = trav->next;
    }
    printf("NULL\n");
}