#include <stdio.h>
#include <stdlib.h>

#define INF 999
#define SIZE 6

typedef int Graph[SIZE][SIZE];

void initGraph(Graph G);
void displayGraph(Graph G);
void populate(Graph G);
int Prims(Graph G, int V[], int start);

void main() {
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
}

void initGraph(Graph G) {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            G[i][j] = INF;
        }
    }
}

void displayGraph(Graph G) {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            printf("\t%d ", G[i][j]);
        }
        printf("\n");
    }
}

void populate(Graph G) {
    G[0][1] = 1;
    G[0][2] = 5;
    G[0][3] = 4;
    G[0][4] = 6;
    G[0][5] = 5;
    G[1][0] = 1;
    G[1][2] = 5;
    G[1][5] = 6;
    G[2][0] = 5;
    G[2][1] = 5;
    G[2][3] = 2;
    G[3][0] = 4;
    G[3][2] = 2;
    G[3][4] = 1;
    G[4][0] = 6;
    G[4][3] = 1;
    G[4][5] = 3;
    G[5][0] = 5;
    G[5][1] = 6;
    G[5][4] = 3;
}

int Prims(Graph G, int V[], int start){
    int U[SIZE] = {0}; //initialize set U to contain all vertices,  set to 0
    U[start] = 1; //Add the starting vertex to U
    int totalCost = 0; //Total cost of the minimum spanning tree
    int numEdges = 0; //number of edges in the MST
    int finished = 0; //Flag to indicare if algorithm is finished simulating
    int minCost, minU, minV, u, v;

    while(!finished){
        minCost = INF;
        
        //Find the minimum cost edge (u,v) such that u is an element of U and v is an element of V-U
        for(u = 0; u < SIZE; u++){
            if(U[u]){ //check if vertex u is included in set U
                for(v = 0; v < SIZE; v++){
                    if(!U[v] && G[u][v] < minCost){
                        minCost = G[u][v];
                        minU = u;
                        minV = v;
                    }
                }
            }
        }
        printf("Edge(%d, %d) | Cost: %d\n", minU, minV, minCost);
        if(minCost == INF){
            //no more edges to add, set the finished flag
            finished = 1;
        } else{
            //add v to U
            U[minV] = 1;
            totalCost += minCost;
            numEdges++;

            if(numEdges == SIZE -1){
                finished = 1;
            }
        }
    }

    return totalCost;
}


