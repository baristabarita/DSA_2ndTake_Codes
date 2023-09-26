#include<stdio.h>
#include<stdlib.h>
#define SIZE 7
#define VISITED 'V'
#define UNVISITED 'U'
#define MAX 999

typedef int Graph[SIZE][SIZE];

typedef struct{
	int elem[SIZE];
	int front,rear;
}Queue;

//Mark
struct{
	unsigned char vertex[SIZE];
	int count;	
}mark;

void enqueue(int,Queue*);
int front(Queue);
void initGraph(Graph);
void dequeue(Queue*);
void populate(Graph);
void insertVertex(int,int,Graph);
void bfs(Graph A,int vertex);
void displayGraph(Graph L);
void initMark();

void main(){
	Graph A={{MAX,1,1,MAX,MAX,MAX,MAX},
	         {MAX,MAX,1,1,MAX,MAX,MAX},
	         {1,MAX,MAX,MAX,MAX,MAX,MAX},
	         {1,MAX,1,MAX,MAX,MAX,MAX},
	         {MAX,MAX,MAX,MAX,MAX,1,1},
	         {MAX,1,MAX,MAX,MAX,MAX,MAX},
	         {MAX,MAX,MAX,1,MAX,1,MAX},
	        };
    initMark();
	bfs(A,4);
	if(mark.count<SIZE){
		int x;
		for(x=0;mark.vertex[x]!=UNVISITED;x++){}
		bfs(A,x);
	}
}

void initQueue(Queue*A){
	A->front=0;
	A->rear=-1;
}

void enqueue(int elem,Queue*Q){
	if((Q->rear+2)%SIZE!=Q->front){
		Q->rear=(Q->rear+1)%SIZE;
		Q->elem[Q->rear]=elem;
	}	
}

void initMark(){
	int x;
	for(x=0;x<SIZE;x++){
		mark.vertex[x]=UNVISITED;
	}
	mark.count=0;
}

int front(Queue Q){
	return (Q.rear+1)%SIZE!=Q.front ? Q.elem[Q.front] : -1;
}

void dequeue(Queue*Q){
	if((Q->rear+1)%SIZE!=Q->front){
		Q->front=(Q->front+1)%SIZE;
	}
}

void bfs(Graph A,int vertex){
    Queue Q;
    initQueue(&Q);
    int x,y;
    mark.vertex[vertex]=VISITED;
    mark.count++;
    enqueue(vertex,&Q);
    while((Q.rear+1)%SIZE!=Q.front){
        x = front(Q);
        printf("%d ",x);
        dequeue(&Q);
        for(y=0;y<SIZE;y++){
            if(A[x][y]==1){
                if(mark.vertex[y]==UNVISITED){
                    mark.vertex[y]=VISITED;
                    mark.count++;
                    enqueue(y,&Q);
                }
            }
        }
    }
}