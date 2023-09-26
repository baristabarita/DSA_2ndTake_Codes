#include<stdio.h>
#include<stdlib.h>

#define SIZE 7
#define VISITED 'V'
#define UNVISITED 'U'

typedef struct node {
    int data;
    struct node* next;
} *graphPtr;

typedef graphPtr Graph[SIZE];

typedef struct {
    char vertex[SIZE];
    int count;
} mark;

void initGraph(Graph G);
void initMarked(mark* M);
void insert(Graph G, int parent, int node);
void populateGraph(Graph G);
void displayGraph(Graph G);
void displayMarked(mark M);
void dfs(Graph G, mark* M, int vertex);

void main() {
    Graph G;
    mark M;
    printf("\n***** Initialize the Graph and Mark ******\n");
    initGraph(G);
    initMarked(&M);
    displayGraph(G);
    displayMarked(M);
    printf("\n***** Populate the Graph ******\n");
    populateGraph(G);
    displayGraph(G);
    printf("\n***** Simulating DFS ******\n");
    dfs(G, &M, 4);
    // To check if all vertices are visited
    if (M.count < SIZE - 1) {
        dfs(G, &M, M.count);
    }
    printf("\n*****  Mark Array after DFS simulation ******\n");
    displayMarked(M);

}

// Initialization Functions

// Initialize the graph by setting all entries to NULL
void initGraph(Graph G) {
    int i;
    for (i = 0; i < SIZE; i++) {
        G[i] = NULL;
    }
}

// Initialize the marked array by setting all vertices to UNVISITED and count to 0
void initMarked(mark* M) {
    int i;
    for (i = 0; i < SIZE; i++) {
        M->vertex[i] = UNVISITED;
    }
    M->count = 0;
}

// Insert a node into the graph
void insert(Graph G, int parent, int node) {
    graphPtr* trav;
    // Find the appropriate position to insert the node
    for (trav = &G[parent]; (*trav) != NULL && (*trav)->data != node; trav = &(*trav)->next) {}
    if ((*trav) == NULL) {
        // If the node is not found, create a new node and insert it
        *trav = (graphPtr)malloc(sizeof(struct node));
        if (*trav != NULL) {
            (*trav)->data = node;
            (*trav)->next = NULL;
        }
    }
}

// Populate the graph with edges
void populateGraph(Graph G) {
    insert(G, 0, 1);
    insert(G, 0, 2);
    insert(G, 1, 2);
    insert(G, 1, 3);
    insert(G, 2, 0);
    insert(G, 3, 0);
    insert(G, 3, 2);
    insert(G, 4, 5);
    insert(G, 4, 6);
    insert(G, 5, 1);
    insert(G, 6, 3);
    insert(G, 6, 5);
}

// Display the graph
void displayGraph(Graph G) {
    int i;
    graphPtr trav;
    for (i = 0; i < SIZE; i++) {
        printf("[%d]", i);
        for (trav = G[i]; trav != NULL; trav = trav->next) {
            printf("%2d -> ", trav->data);
        }
        printf("\n");
    }
}

// Display the marked array
void displayMarked(mark M) {
    int i;
    printf("Mark: ");
    for (i = 0; i < SIZE; i++) {
        printf("%c ", M.vertex[i]);
    }
    printf("\nCurrent Marked Count: %d\n", M.count);
}

// Depth First Search (DFS)
void dfs(Graph G, mark* M, int vertex) {
    int w;
    // Set the starting vertex as visited and increment the count for the number of times visited
    M->vertex[vertex] = VISITED;
    M->count++;
    graphPtr trav;
    printf("Currently at vertex/node: %d\n", vertex);
    // Iterate over each adjacent vertex of the current vertex
    for (trav = G[vertex]; trav != NULL; trav = trav->next) {
        // Set 'w' as the next vertex to be visited
        w = trav->data;
        // If 'w' is unvisited, recursively perform DFS
        if (M->vertex[w] == UNVISITED) {
            dfs(G, M, w);
        }
    }
}
