#include<stdio.h>
#include<stdlib.h>
#define SIZE 7
#define VISITED 'V'
#define UNVISITED 'U'

typedef struct node{
    int elem;
    struct node* link;
} *gptr;

typedef gptr Graph[SIZE];

typedef struct cell{
    int child;
    struct cell* next;
} *Header;

typedef struct{
    Header H[SIZE];
    int root;
} Tree;

typedef struct{
    int elem[SIZE];
    int front, rear;
} Queue;

// Mark globally declared
struct{
    char vertex[SIZE];
    int count;    
} mark;

// Graph Functions
void initGraph(Graph G);
void insertEdge(Graph G, int w, int v);
void displayGraph(Graph G);
void populateGraph(Graph G);

// Tree Functions
void initTree();
void insertChild(Tree *T, int parent, int child);
void displayTree(Tree T);

// Queue Functions
void initQueue(Queue *Q);
void ENQUEUE(int elem, Queue *Q);
void DEQUEUE(Queue *Q);
int Front(Queue Q);
int isEmpty(Queue Q);

// Mark Functions
void initMark();
void displayMark();

void bfs(Graph G, int vertex);

// Globally Declared Tree
Tree T;

void main(){
    printf("\n***** Initialization *****\n");
    Graph G;
    initGraph(G);
    initTree();
    initMark();

    displayGraph(G);
    displayTree(T);
    displayMark();

    printf("\n***** Populate Graph *****\n");
    populateGraph(G);
    displayGraph(G);

    printf("\n***** BFS Simulation *****\n");
    int start = 4;
    T.root = start;
    bfs(G, start);
    // Recursion for BFS
    if(mark.count < SIZE){
        int ndx;
        for(ndx = 0; mark.vertex[ndx] != UNVISITED; ndx++){}
        bfs(G, ndx);
    }

    printf("\n***** Tree and Mark after BFS Simulation *****\n");
    printf("\nCurrent Tree Root: %d\n", T.root);
    displayTree(T);
    displayMark();
}

// Graph Functions
void initGraph(Graph G){
    int i;
    for(i = 0; i < SIZE; i++){
        G[i] = NULL;
    }
}

void insertEdge(Graph G, int w, int v){
    // w is the head/parent, v is the tail/child to be inserted
    gptr *trav;
    for(trav = &G[w]; (*trav) != NULL; trav = &(*trav)->link){}

    if(*trav == NULL){
        *trav = (gptr)malloc(sizeof(struct node));
        if(*trav != NULL){
            (*trav)->elem = v;
            (*trav)->link = NULL;
        }
    }
}

void displayGraph(Graph G){
    int i;
    gptr trav;
    printf("\nGraph: \n");
    for(i = 0; i < SIZE; i++){
        printf("[%d]", i);
        for(trav = G[i]; trav != NULL; trav = trav->link){
            printf("%2d -> ", trav->elem);
        }
        printf("\n");
    }
}

void populateGraph(Graph G){
    insertEdge(G, 0, 1);
    insertEdge(G, 0, 2);
    insertEdge(G, 1, 2);
    insertEdge(G, 1, 3);
    insertEdge(G, 2, 0);
    insertEdge(G, 3, 0);
    insertEdge(G, 3, 2);
    insertEdge(G, 4, 5);
    insertEdge(G, 4, 6);
    insertEdge(G, 5, 1);
    insertEdge(G, 6, 3);
    insertEdge(G, 6, 5);
}

// Tree Functions
void initTree(){
    int i;
    for(i = 0; i < SIZE; i++){
        T.H[i] = NULL;
    }
    T.root = -1; // Probably not needed
}

void insertChild(Tree *T, int parent, int child){
    Header *trav;
    for(trav = &T->H[parent]; *trav != NULL && (*trav)->child != child; trav = &(*trav)->next){}

    if(*trav == NULL){
        *trav = (Header)malloc(sizeof(struct cell));
        if(*trav != NULL){
            (*trav)->child = child;
            (*trav)->next = NULL;
        }
    }
}

void displayTree(Tree T){
    int i;
    Header trav;
    printf("\nTree: \n");
    for(i = 0; i < SIZE; i++){
        printf("[%d] ->", i);
        if(T.H[i] != NULL){
            for(trav = T.H[i]; trav != NULL; trav = trav->next){
                printf("%2d -> ", trav->child );
            }
        }
        printf("\n");
    }
}

// Queue Functions
void initQueue(Queue *Q){
    Q->front = 0;
    Q->rear = -1;
}

void ENQUEUE(int elem, Queue *Q){
    // Checks if the queue is not full and that there is space to enqueue a new element
    if((Q->rear + 2) % SIZE != Q->front){
        Q->rear = (Q->rear + 1) % SIZE; // Essentially Q->rear++
        Q->elem[Q->rear] = elem; // Places the new element in the rear of the queue
    }
}

void DEQUEUE(Queue *Q){
    // Checks if the queue is not empty. It verifies whether the queue contains any elements to be dequeued.
    if((Q->rear + 1) % SIZE != Q->front){
        Q->front = (Q->front + 1) % SIZE; // Essentially Q->front++
    }
}

int Front(Queue Q){
    // Checks if the queue is not empty
    return ((Q.rear + 1) % SIZE != Q.front) ? Q.elem[Q.front] : -1;
}

int isEmpty(Queue Q){
    // Checks if the queue is empty
    return ((Q.rear + 1) % SIZE == Q.front) ? 1 : 0;
}

// Mark Functions
void initMark(){
    int i;
    for(i = 0; i < SIZE; i++){
        mark.vertex[i] = UNVISITED;
    }
    mark.count = 0;
}

void displayMark(){
    int i;
    printf("Mark: ");
    for(i = 0; i < SIZE; i++){
        printf("%c ", mark.vertex[i]);
    }
    printf("\nCurrent Marked Count: %d\n", mark.count);
}

void bfs(Graph G, int vertex){
    Queue Q;
    initQueue(&Q);
    gptr trav;
    int x, y; // The vertices

    mark.vertex[vertex] = VISITED;
    mark.count++;
    ENQUEUE(vertex, &Q);

    while(isEmpty(Q) == 0){
        x = Front(Q);
        printf("Visited vertex %d\n", x);
        DEQUEUE(&Q);

        // For each vertex y adjacent to x
        for(trav = G[x]; trav != NULL; trav = trav->link){
            y = trav->elem;
            
            // If mark[y] == unvisited
            if(mark.vertex[y] == UNVISITED){
                mark.vertex[y] = VISITED;
                mark.count++;
                ENQUEUE(y, &Q);
                insertChild(&T, x, y);
            }
        }
    }
}
