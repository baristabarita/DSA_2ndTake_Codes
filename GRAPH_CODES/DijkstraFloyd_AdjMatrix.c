#include <stdio.h>
#include <stdlib.h>

#define INF 999
#define SIZE 5

typedef int Graph[SIZE][SIZE];

void initGraph(Graph G);
void populate(Graph G);
void display(Graph G);
void displayDijk(int D[]);
int *Dijkstra(Graph G, int startV);
void Floyd(Graph A, Graph C);
int FindCenter(Graph A);

void main(){
    Graph G, A;

    // Initialize and display the graph matrix
    printf("\n***** Graph Matrix After Initialization *****\n");
    initGraph(G);
    display(G);

    // Populate and display the graph matrix
    printf("\n***** Graph Matrix After Population *****\n");
    populate(G);
    display(G);

    // Perform Dijkstra's algorithm and display the results
    printf("\n***** Dijkstra's Algorithm *****\n");
    int *dijk = Dijkstra(G, 0);
    displayDijk(dijk);

    // Perform Floyd's algorithm and display the results
    printf("\n***** Floyd's Algorithm *****\n");
    Floyd(A, G);
    display(A);

    // Find the center of the graph using Floyd's algorithm and display the result
    printf("\nCenter of the Graph: %d", FindCenter(A));
}

// Initialize the graph matrix with INF values
void initGraph(Graph G){
    int i, j;
    for(i = 0; i < SIZE; i++){
        for(j = 0; j < SIZE; j++){
            G[i][j] = INF;
        }
    }
}

// Populate the graph matrix with specific values
void populate(Graph G){
    G[0][1] = 10;
    G[0][3] = 30;
    G[0][4] = 100;
    G[1][2] = 50;
    G[2][0] = 20;
    G[2][4] = 10;
    G[3][2] = 20;
    G[3][4] = 60;
}

// Display the graph matrix
void display(Graph G){
    int i, j;
    for(i = 0; i < SIZE; i++){
        for(j = 0; j < SIZE; j++){
            printf("\t%d", G[i][j]);
        }
        printf("\n");
    }
}

// Perform Dijkstra's algorithm on the graph to find the shortest paths from a given start vertex
int *Dijkstra(Graph G, int startV){
    int S[SIZE], i, j, x, sum = 0, w, Scount = 0, min = INF;
    int V[SIZE] = {0,1,2,3,4};
    int *D = (int*)calloc(1,sizeof(int)*SIZE);

    if(D != NULL){
        S[Scount++] = startV;

        // Initialize D with distances from the start vertex
        for(i = 1; i < SIZE; i++){
            D[i] = G[startV][i];
        }

        for(i = 1; i < SIZE; i++){
            // A. Choose a vertex w in V-S such that D[w] is a minimum (except the source vertex)
            for(x = 0; x < SIZE; x++){
                for(j = 0; j < Scount && V[x] != S[j]; j++){}
                if(j == Scount && D[V[x]] < min){
                    min = D[V[x]];
                    w = V[x];
                }
            }

            // B. Add w to S
            S[Scount++] = w;

            // C. Update the distances of vertices in V-S using w
            for(x = 0; x < SIZE; x++){
                for(j = 0; j < Scount && V[x] != S[j]; j++){}
                if(j == Scount){
                    sum = D[w] + G[w][V[x]];
                    D[V[x]] = ( D[V[x]] < sum ) ? D[V[x]] : sum;
                }
            }
            min = INF;
        }
    }
    return D;
}

// Display the result of Dijkstra's algorithm
void displayDijk(int D[]){
    int i, x;
    printf("Source\tCost\n");
    for(x = 0; x < SIZE; x++){
        printf("%d\t%d\n", x, D[x]);
    }
}

// Perform Floyd's algorithm to find the shortest paths between all pairs of vertices
void Floyd(Graph A, Graph C){
    // Graph A will store the shortest paths from any source vertex to any destination vertex
    // Graph C is the labeled adjacency matrix
    int i, j, k;

    // Copy the labeled adjacency matrix to A
    for(i = 0; i < SIZE; i++){
        for(j = 0; j < SIZE; j++){
            A[i][j] = C[i][j];
        }
    }

    // Set the diagonal elements to zero
    for(i = 0; i < SIZE; i++){
        A[i][i] = 0;
    }

    // Perform the Floyd's algorithm
    for(k = 0; k < SIZE; k++){
        for(i = 0; i < SIZE; i++){
            for(j = 0; j < SIZE; j++){
                if(A[i][k] + A[k][j] < A[i][j]){
                    A[i][j] = A[i][k] + A[k][j];
                }
            }
        }
    }
}

// Find the center of the graph using Floyd's algorithm
int FindCenter(Graph A){
    int max, x, y;
    int ecc[SIZE];

    // Calculate the eccentricity for each vertex
    for(y = 0; y < SIZE; y++){
        max = A[0][y];
        for(x = 1; x < SIZE; x++){
            max = (max > A[x][y]) ? max : A[x][y];
        }
        ecc[y] = max;
    }

    // Find the vertex with the minimum eccentricity (the center)
    max = 0;
    for(x = 1; x < SIZE; x++){
        max = (ecc[max] < ecc[x])? max: x;
    }
    return max;
}
