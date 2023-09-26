#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100
#define INF 99999999

void dijkstra(int graph[MAX_NODES][MAX_NODES], int n, int start_node);

int main() {
    int n, start_node;
    int graph[MAX_NODES][MAX_NODES];

    // Read the number of nodes and the adjacency matrix
    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    // Read the start node
    printf("Enter the start node: ");
    scanf("%d", &start_node);

    // Call Dijkstra's algorithm to find the shortest path from the start node to all other nodes
    dijkstra(graph, n, start_node);

    return 0;
}

void dijkstra(int graph[MAX_NODES][MAX_NODES], int n, int start_node) {
    int dist[MAX_NODES]; // Distance from start node to each node
    int visited[MAX_NODES]; // Whether each node has been visited
    int count, min_dist, next_node;

    // Initialize the distance array and visited array
    for (int i = 0; i < n; i++) {
        dist[i] = graph[start_node][i];
        visited[i] = 0;
    }

    // Distance from start node to itself is 0
    dist[start_node] = 0;
    visited[start_node] = 1;
    count = 1;

    // Dijkstra's algorithm
    while (count < n - 1) {
        min_dist = INF;

        // Find the node with the minimum distance that has not been visited
        for (int i = 0; i < n; i++) {
            if (dist[i] < min_dist && !visited[i]) {
                min_dist = dist[i];
                next_node = i;
            }
        }

        // Mark the node as visited
        visited[next_node] = 1;

        // Update the distance array
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                if (min_dist + graph[next_node][i] < dist[i]) {
                    dist[i] = min_dist + graph[next_node][i];
                }
            }
        }

        count++;
    }

    // Print the shortest distances
    printf("Node\tShortest Distance\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\n", i, dist[i]);
    }
}
