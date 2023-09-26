#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100
#define INFINITY 999999

typedef struct Node {
    int vertex;
    int weight;
    struct Node* next;
} Node;

typedef struct Graph {
    int num_vertices;
    Node* lists[MAX_VERTICES];
} Graph;

typedef struct PriorityQueue {
    int size;
    int* elements;
} PriorityQueue;

Node* create_node(int v, int weight) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->vertex = v;
    node->weight = weight;
    node->next = NULL;
    return node;
}

Graph* create_graph(int num_vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->num_vertices = num_vertices;
    for (int i = 0; i < num_vertices; i++) {
        graph->lists[i] = NULL;
    }
    return graph;
}

void add_edge(Graph* graph, int src, int dest, int weight) {
    Node* node = create_node(dest, weight);
    node->next = graph->lists[src];
    graph->lists[src] = node;
}

PriorityQueue* create_priority_queue(int capacity) {
    PriorityQueue* queue = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    queue->size = 0;
    queue->elements = (int*)malloc(sizeof(int) * capacity);
    return queue;
}

void enqueue(PriorityQueue* queue, int value) {
    queue->elements[queue->size++] = value;
}

int dequeue(PriorityQueue* queue) {
    int min_index = 0;
    for (int i = 1; i < queue->size; i++) {
        if (queue->elements[i] < queue->elements[min_index]) {
            min_index = i;
        }
    }
    int min_value = queue->elements[min_index];
    queue->elements[min_index] = queue->elements[--queue->size];
    return min_value;
}

int is_empty(PriorityQueue* queue) {
    return queue->size == 0;
}

int* dijkstra(Graph* graph, int source) {
    int* distances = (int*)malloc(sizeof(int) * graph->num_vertices);
    for (int i = 0; i < graph->num_vertices; i++) {
        distances[i] = INFINITY;
    }
    distances[source] = 0;

    PriorityQueue* queue = create_priority_queue(graph->num_vertices);
    enqueue(queue, source);

    while (!is_empty(queue)) {
        int u = dequeue(queue);

        Node* current = graph->lists[u];
        while (current != NULL) {
            int alt = distances[u] + current->weight;
            if (alt < distances[current->vertex]) {
                distances[current->vertex] = alt;
                enqueue(queue, current->vertex);
            }
            current = current->next;
        }
    }

    return distances;
}

int main() {
    Graph* graph = create_graph(5);
    add_edge(graph, 0, 1, 10);
    add_edge(graph, 0, 3, 30);
    add_edge(graph, 0, 4, 100);
    add_edge(graph, 1, 2, 50);
    add_edge(graph, 2, 1, 20);
    add_edge(graph, 2, 4, 10);
    add_edge(graph, 3, 2, 20);
    add_edge(graph, 3, 4, 60);

    int source = 0;
    int* distances = dijkstra(graph, source);

    printf("Shortest distances from vertex %d:\n", source);
    for (int i = 0; i < graph->num_vertices; i++) {
        printf("Vertex %d: %d\n", i, distances[i]);
    }

    free(distances);
    free(graph);

    return 0;
}
