#include <stdio.h>
#define MAX 5

typedef struct {
    char Elem[MAX];
    int front;
    int rear;   
}Queue;

void initQueue(Queue *);
int isEmpty(Queue);
int isFull(Queue);
void enqueue(Queue *, char);
void dequeue(Queue *);
char front(Queue);
void displayQueue(Queue);

void main() {
    Queue Q;
    initQueue(&Q);
    enqueue(&Q, 'A');
    enqueue(&Q, 'B');
    enqueue(&Q, 'C');
    displayQueue(Q);
}

void initQueue(Queue *Q) {
    Q->front = 1;
    Q->rear = 0;
}

int isEmpty(Queue Q) {
    return ((Q.rear+1)%MAX == Q.front) ? 1 : 0;
}

int isFull(Queue Q) {
    return ((Q.rear+2)%MAX == Q.front) ? 1 : 0;
}

void enqueue(Queue *Q, char data) {
    if (isFull(*Q) != 1) {
        Q->rear = (Q->rear+1)%MAX;
        Q->Elem[Q->rear] = data;
    }
}

void dequeue(Queue *Q) {
    if (isEmpty(*Q) != 1) {
        Q->front = (Q->front+1)%MAX;
    }
}

char front(Queue Q) {
    return (isEmpty(Q) != 1) ? Q.Elem[Q.front] : '#';
}

void displayQueue(Queue Q) {
    
    int idx;
	printf("\nContent of queue:\n");
    if ((Q.rear+1)%MAX != Q.front){
        for (idx = Q.front; idx != (Q.rear+1)%MAX; idx = (idx+1)%MAX){
		    printf("Q.Elem[%d] = '%c';\n", idx, Q.Elem[idx]);
	    }
    } else {
        printf("\nQueue is empty.\n");
    }
}
