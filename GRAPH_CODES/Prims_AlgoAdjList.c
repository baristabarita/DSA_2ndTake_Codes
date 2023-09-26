#include <stdio.h>
#include <stdlib.h>

#define SIZE 6

typedef struct node {
    int weight;
    int node;
    struct node* link;
} *gptr;

typedef gptr Graph[SIZE];

void initGraph(Graph G);
void displayGraph(Graph G);
void insertEdge(Graph G, int parent, int child, int weight);
void populate(Graph G);
int Prims(Graph G, int V[], int start);

int main() {
    Graph G;
    int V[] = {0, 1, 2, 3, 4, 5};
    int start = 0;
    printf("\n**** Initialization of Graph ****\n");
    initGraph(G);
    displayGraph(G);
    printf("\n**** Populating Graph ****\n");
    populate(G);
    displayGraph(G);

    printf("\n**** Simulate Prims Algorithm ****\n");
    // Function call for Prims
    printf("Total Costs: %d\n", Prims(G, V, start));
    return 0;
}

void initGraph(Graph G) {
    int i;
    for (i = 0; i < SIZE; i++) {
        G[i] = NULL;
    }
}

void displayGraph(Graph G) {
    int i;
    gptr trav;
    for (i = 0; i < SIZE; i++) {
        printf("[%d]", i);
        for (trav = G[i]; trav != NULL; trav = trav->link) {
            printf("%2d ->", trav->node);
        }
        printf("\n");
    }
}

void insertEdge(Graph G, int parent, int child, int weight) {
    int i;
    gptr* trav;
    for (trav = &G[parent]; (*trav) != NULL; trav = &(*trav)->link) {
    }
    if (*trav == NULL) {
        *trav = (gptr)malloc(sizeof(struct node));
        if (*trav != NULL) {
            (*trav)->weight = weight;
            (*trav)->node = child;
            (*trav)->link = NULL;
        }
    }
}

void populate(Graph G) {
    insertEdge(G, 0, 1, 1);
    insertEdge(G, 0, 2, 5);
    insertEdge(G, 0, 3, 4);
    insertEdge(G, 0, 4, 6);
    insertEdge(G, 0, 5, 5);
    insertEdge(G, 1, 0, 1);
    insertEdge(G, 1, 2, 5);
    insertEdge(G, 1, 5, 6);
    insertEdge(G, 2, 0, 5);
    insertEdge(G, 2, 1, 5);
    insertEdge(G, 2, 3, 2);
    insertEdge(G, 3, 0, 4);
    insertEdge(G, 3, 2, 2);
    insertEdge(G, 3, 4, 1);
    insertEdge(G, 4, 0, 6);
    insertEdge(G, 4, 3, 1);
    insertEdge(G, 4, 5, 3);
    insertEdge(G, 5, 0, 5);
    insertEdge(G, 5, 1, 6);
    insertEdge(G, 5, 4, 3);
}

int Prims(Graph G, int V[], int start) {
    int U[SIZE] = {0};      // U set to contain {0}
    U[start] = 1;           // Initialize the start vertex in U
    int VSize = SIZE-1;    // Size of V (excluding the start vertex)
    int totalCost = 0;      // Total cost of MST
    int minCost, minU, minV, i;
    gptr trav;

    while(VSize > 0) {
        minCost = minU = minV = -1;

        //Find minimum cost edge(u,v)
        for(i = 0; i < SIZE; i++){
            if(U[i]){ //check if vertex i is included in set U
                trav = G[i];
                while(trav != NULL){
                    if(!U[trav->node] && (minCost == -1 || trav->weight < minCost)){
                        minCost = trav->weight;
                        minU = i;
                        minV = trav->node;
                    }
                    trav = trav->link;
                }
            }
        }
        printf("Edge(%d,%d) | Cost: %d\n",minU,minV,minCost);
        if(minV != -1){
            //Add v to U
            U[minV] = 1;
            totalCost += minCost;
            VSize--;
        }
    }
    return totalCost;
}
