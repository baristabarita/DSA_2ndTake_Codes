#include <stdio.h>
#include <stdlib.h>

#define INF 999 // Infinity value for unconnected nodes

// Structure for representing a node in the adjacency list
struct Node {
    int destination;
    int weight;
    struct Node* next;
};

// Function to create a new node in the adjacency list
struct Node* createNode(int destination, int weight) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->destination = destination;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// Function to add an edge to the adjacency list
void addEdge(struct Node** adjacencyList, int src, int dest, int weight) {
    struct Node* newNode = createNode(dest, weight);
    newNode->next = adjacencyList[src];
    adjacencyList[src] = newNode;
}

// Function to find the minimum distance vertex in the set of unvisited vertices
int findMinDistance(int* distance, int* visited, int numVertices) {
    int minDistance = INF;
    int minVertex;

    for (int v = 0; v < numVertices; v++) {
        if (visited[v] == 0 && distance[v] <= minDistance) {
            minDistance = distance[v];
            minVertex = v;
        }
    }

    return minVertex;
}

// Function to perform Dijkstra's algorithm on the given graph
void dijkstra(struct Node** adjacencyList, int numVertices, int source) {
    int* distance = (int*)malloc(numVertices * sizeof(int));
    int* visited = (int*)malloc(numVertices * sizeof(int));

    for (int v = 0; v < numVertices; v++) {
        distance[v] = INF;
        visited[v] = 0;
    }

    distance[source] = 0;

    for (int count = 0; count < numVertices - 1; count++) {
        int u = findMinDistance(distance, visited, numVertices);
        visited[u] = 1;

        struct Node* currentNode = adjacencyList[u];
        while (currentNode != NULL) {
            int v = currentNode->destination;
            int weight = currentNode->weight;

            if (!visited[v] && distance[u] != INF && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
            }

            currentNode = currentNode->next;
        }
    }

    printf("Dijkstra's Algorithm:\n");
    printf("Vertex\tDistance from Source\n");
    for (int v = 0; v < numVertices; v++) {
        printf("%d\t%d\n", v, distance[v]);
    }

    free(distance);
    free(visited);
}

// Function to perform Floyd's algorithm on the given graph
void floyd(struct Node** adjacencyList, int numVertices) {
    int** distance = (int**)malloc(numVertices * sizeof(int*));

    for (int i = 0; i < numVertices; i++) {
        distance[i] = (int*)malloc(numVertices * sizeof(int));
        for (int j = 0; j < numVertices; j++) {
            if (i == j)
                distance[i][j] = 0;
            else
                distance[i][j] = INF;
        }
    }

    for (int i = 0; i < numVertices; i++) {
        struct Node *currentNode = adjacencyList[i];
        while(currentNode != NULL){
            int j = currentNode->destination;
            int weight = currentNode->weight;
            distance[i][j] = weight;
            currentNode = currentNode->next;
        }
    }
    for (int k = 0; k < numVertices; k++) {
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                if (distance[i][k] != INF && distance[k][j] != INF && distance[i][k] + distance[k][j] < distance[i][j]) {
                        distance[i][j] = distance[i][k] + distance[k][j];
                }
            }
        }
    }

    printf("\nFloyd's Algorithm:\n");
    printf("Pair\t\tDistance\n");
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            printf("%d -> %d\t\t%d\n", i, j, distance[i][j]);
        }
    }

    for (int i = 0; i < numVertices; i++) {
        free(distance[i]);
    }
    free(distance);
}    
        
int main() {
    int numVertices = 5;
    struct Node** adjacencyList = (struct Node**)malloc(numVertices * sizeof(struct Node*));
    // Initialize the adjacency list
    for (int i = 0; i < numVertices; i++) {
        adjacencyList[i] = NULL;
    }

    // Add edges to the graph
    addEdge(adjacencyList, 0, 1, 10);
    addEdge(adjacencyList, 0, 3, 30);
    addEdge(adjacencyList, 0, 4, 100);
    addEdge(adjacencyList, 1, 2, 50);
    addEdge(adjacencyList, 2, 0, 20);
    addEdge(adjacencyList, 2, 4, 10);
    addEdge(adjacencyList, 3, 2, 20);
    addEdge(adjacencyList, 3, 4, 60);
    

    // Perform Dijkstra's algorithm
    int source = 0;
    dijkstra(adjacencyList, numVertices, source);

    // Perform Floyd's algorithm
    floyd(adjacencyList, numVertices);

    // Free the memory
    for (int i = 0; i < numVertices; i++) {
        struct Node* currentNode = adjacencyList[i];
        while (currentNode != NULL) {
        struct Node* temp = currentNode;
        currentNode = currentNode->next;
        free(temp);
        }
    }
    free(adjacencyList);

    return 0;
}