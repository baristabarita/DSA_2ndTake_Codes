#include<stdio.h>
#include<stdlib.h>

#define INF 999
#define SIZE 6

typedef int Graph[SIZE][SIZE];

// Function prototypes
void initGraph(Graph G);
void displayGraph(Graph G);
void populateGraph(Graph G);
int find(int parent[], int vertex);
void unionSet(int parent[], int rank[], int x, int y);
int kruskals(Graph G, int V[]);

void main(){
    Graph G;
    int V[] = {0,1,2,3,4,5};
    initGraph(G);
    populateGraph(G);
    displayGraph(G);
    printf("Min Cost: %d", kruskals(G,V));
}

// Initialize the graph with INF (infinite) values for all edges
void initGraph(Graph G){
    int i, j;
    for(i = 0; i < SIZE; i++){
        for(j = 0; j < SIZE; j++){
            G[i][j] = INF;
        }
    }
}

// Display the graph
void displayGraph(Graph G){
    int i, j;
    for(i = 0; i < SIZE; i++){
        for(j = 0; j < SIZE; j++){
            printf("%5d ", G[i][j]);
        }
        printf("\n");
    }    
}

// Populate the graph with edge weights
void populateGraph(Graph G){
    G[0][1] = G[1][0] = 1;
    G[0][2] = G[2][0] = 5;
    G[0][3] = G[3][0] = 4;
    G[0][4] = G[4][0] = 6;
    G[0][5] = G[5][0] = 5;
    G[1][2] = G[2][1] = 5;
    G[1][5] = G[5][1] = 6;
    G[2][3] = G[3][2] = 2;
    G[3][4] = G[4][3] = 1;
    G[4][5] = G[5][4] = 3;
}

// Find function for disjoint-set data structure
// Finds the representative (root) of the set to which the given vertex belongs
int find(int parent[], int vertex){
    if(parent[vertex] != vertex)
        parent[vertex] = find(parent, parent[vertex]); // Path compression optimization
    return parent[vertex];
}

// Union function for disjoint-set data structure
// Combines two sets (components) by attaching the root of one set to the root of the other set
void unionSet(int parent[], int rank[], int x, int y){
    int rootX = find(parent, x); // Find the root of the set containing vertex x
    int rootY = find(parent, y); // Find the root of the set containing vertex y
    if(rank[rootX] < rank[rootY]){
        parent[rootX] = rootY; // Attach the root of set X to the root of set Y
    }
    else if(rank[rootX] > rank[rootY]){
        parent[rootY] = rootX; // Attach the root of set Y to the root of set X
    }
    else{
        parent[rootY] = rootX; // Attach the root of set Y to the root of set X
        rank[rootX]++; // Increment the rank of the new root (X)
    }
}


// Kruskal's algorithm implementation
int kruskals(Graph G, int V[]){
    int parent[SIZE]; // Parent array for disjoint-set data structure
    int rank[SIZE]; // Rank array for disjoint-set data structure
    int minCost = 0; // Minimum cost of the spanning tree
    int edgeCount = 0; // Count of edges included in the spanning tree
    
    // Initialize parent and rank arrays
    for(int i = 0; i < SIZE; i++){
        parent[i] = i; // Initially, each vertex is its own parent
        rank[i] = 0; // Initially, the rank of each vertex is 0
    }
    
    while(edgeCount < SIZE - 1){
        int minEdge = INF; // Minimum edge weight
        int u = -1; // Source vertex of the minimum edge
        int v = -1; // Destination vertex of the minimum edge
        
        // Find the edge with the minimum cost that connects two different components
        for(int i = 0; i < SIZE; i++){
            for(int j = 0; j < SIZE; j++){
                if(find(parent, i) != find(parent, j) && G[i][j] < minEdge){
                    minEdge = G[i][j];
                    u = i;
                    v = j;
                }
            }
        }
        
        // If a valid edge is found, include it in the spanning tree
        if(u != -1 && v != -1){
            unionSet(parent, rank, u, v); // Union the two components
            printf("Added edge: (%d, %d), Cost: %d\n", u, v, minEdge);
            minCost += minEdge; // Update the minimum cost
            edgeCount++; // Increment the edge count
        }
    }
    
    return minCost; // Return the minimum cost of the spanning tree
}
