#include <stdio.h>
#include <stdlib.h>

#define INF 999999
#define MAX_VERTICES 100

// Node structure for each vertex's adjacency list
typedef struct node {
    int vertex;
    int weight;
    struct node* next;
} Node;

// Graph structure containing the number of vertices and adjacency lists
typedef struct graph {
    int num_vertices;
    Node* lists[MAX_VERTICES];
} Graph;

// Creates a new node with the given vertex and weight
Node* create_node(int v, int w) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->vertex = v;
    node->weight = w;
    node->next = NULL;
    return node;
}

// Creates a new graph with the given number of vertices
Graph* create_graph(int num_vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->num_vertices = num_vertices;
    for (int i = 0; i < num_vertices; i++) {
        graph->lists[i] = NULL;
    }
    return graph;
}

// Adds an edge with the given source, destination, and weight to the graph
void add_edge(Graph* graph, int src, int dest, int weight) {
    Node* node = create_node(dest, weight);
    node->next = graph->lists[src];
    graph->lists[src] = node;
}

// Finds the vertex with the minimum distance that has not yet been visited
int get_min_distance_vertex(int* distances, int* visited, int num_vertices) {
    int min_distance = INF;
    int min_vertex = 0;
    for (int i = 0; i < num_vertices; i++) {
        if (!visited[i] && distances[i] < min_distance) {
            min_distance = distances[i];
            min_vertex = i;
        }
    }
    return min_vertex;
}

// Dijkstra's algorithm for finding the shortest path from a source vertex to all other vertices in a graph
int* dijkstra(Graph* graph, int source) {
    int* distances = (int*)malloc(sizeof(int) * graph->num_vertices);
    int* visited = (int*)malloc(sizeof(int) * graph->num_vertices);

    // Initialize distances and visited arrays
    for (int i = 0; i < graph->num_vertices; i++) {
        distances[i] = INF;
        visited[i] = 0;
    }

    // Distance to source vertex is 0
    distances[source] = 0;

    // Traverse the graph
    for (int i = 0; i < graph->num_vertices - 1; i++) {
        int u = get_min_distance_vertex(distances, visited, graph->num_vertices);
        visited[u] = 1;
        Node* current = graph->lists[u];
        while (current != NULL) {
            int v = current->vertex;
            int w = current->weight;
            if (!visited[v] && distances[u] != INF && distances[u] + w < distances[v]) {
                distances[v] = distances[u] + w;
            }
            current = current->next;
        }
    }

    free(visited);
    return distances;
}

// Main function to test Dijkstra's algorithm
int main() {
    // Create the graph
    Graph* graph = create_graph(5);
    add_edge(graph, 0, 1, 10);
    add_edge(graph, 0, 3, 30);
    add_edge(graph, 0, 4, 100);
    add_edge(graph, 1, 2, 50);
    add_edge(graph, 2, 1, 20);
    add_edge(graph, 2, 4, 10);
    add_edge(graph, 3, 2, 20);
    add_edge(graph, 3, 4, 60);

    // Run Dijkstra's algorithm from source vertex 0
    int source = 0;
    int* distances = dijkstra(graph, source);

    // Print the shortest distances from the source vertex
    printf("Shortest distances from vertex %d:\n", source);
    for (int i = 0; i < graph->num_vertices; i++) {
        printf("Vertex %d: %d\n", i, distances[i]);
    }

    // Free the memory used by the distances array and the graph
    free(distances);
    free(graph);

    return 0;
}
