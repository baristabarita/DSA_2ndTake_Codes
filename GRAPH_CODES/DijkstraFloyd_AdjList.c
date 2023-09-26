//Note: had to ask help from CHATGPT for this shit

#include <stdio.h>
#include <stdlib.h>

#define INF 999 //Infinity Value
#define SIZE 5

//Data structure definition for representing a node in adjacency list
typedef struct node{
    int vertex;
    int weight;
    struct node* next;
} Node;

typedef struct{
    int num_vertices;
    Node* lists[SIZE];
} AdjList;

//Function to initialize the adjacency list
void initializeGraph(AdjList* A){
    int i;
    A->num_vertices = SIZE;
    for(i = 0; i < SIZE; i++){
        A->lists[i] = NULL;
    }
}

//Function to add an edge to the graph
void addEdge(AdjList* A, int src, int dest, int weight){
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = dest;
    newNode->weight = weight;
    newNode->next = A->lists[src];
    A->lists[src] = newNode;
}

//Function to find the vertex with the minimum distance value
int minDistance(int dist[], int visited[]){
    int min = INF, min_index, v;

    for(v = 0; v < SIZE; v++){
        if(visited[v] == 0 && dist[v] <= min){
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

//Function about Dijkstra's Algorithm
void dijkstra(AdjList *A, int src){
    int dist[SIZE];
    int visited[SIZE];
    int i, count, w, v;

    //Initialize distances and visited array
    for(i = 0; i < SIZE; i++){
        dist[i] = INF;
        visited[i] = 0;
    }

    dist[src] = 0;

    for(count = 0; count < SIZE -1; count++){
        w = minDistance(dist, visited);
        visited[w] = 1;

        Node *temp = A->lists[w];
        while(temp != NULL){
            v = temp->vertex;
            
            if(visited[v] == 0 && dist[w] != INF && dist[w] + temp->weight < dist[v]){
                dist[v] = dist[w] + temp->weight;
            }
            temp = temp->next;
        }
    }

    //Print the distances
      printf("Vertex\tDistance from Source\n");
    for(i = 0; i < SIZE; i++){
        printf("%d \t\t %d\n", i, dist[i]);
    }
}

void floyd(AdjList* A){
    int dist[SIZE][SIZE];
    int i, j, k;

    //Initialize the distance matrix
    for(i = 0; i < SIZE; i++){
        for(j = 0; j < SIZE; j++){
            dist[i][j] = INF;
        }
    }

    //Assign the weights of the edges to the distance matrix
    for(i = 0; i < SIZE; i++){
        Node *temp = A->lists[i];
        while(temp != NULL){
            dist[i][temp->vertex] = temp->weight;
            temp = temp->next;
        }
    }
    //set diagonal to 0
    for(i = 0; i < SIZE; i++){
        dist[i][i] = 0;
    }

    //Perform Floyds algo
    for(k = 0; k < SIZE; k++){
        for(i = 0; i < SIZE; i++){
            for(j = 0; j < SIZE; j++){
                if(dist[i][k] + dist[k][j] < dist[i][j]){
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    //Print the distances
    printf("Shortest distances between every pair of vertices: \n");
    for(i = 0; i < SIZE; i++){
        for(j = 0; j < SIZE; j++){
            if(dist[i][j] == INF){
                printf("%d\t", INF);
            } else {
                printf("%d\t", dist[i][j]);
            }
        }
        printf("\n");
    }
}

int main(){
    AdjList graph;
    initializeGraph(&graph);
    // Add edges to the graph
    addEdge(&graph, 0, 1, 10);
    addEdge(&graph, 0, 3, 30);
    addEdge(&graph, 0, 4, 100);
    addEdge(&graph, 1, 2, 50);
    addEdge(&graph, 2, 0, 20);
    addEdge(&graph, 2, 4, 10);
    addEdge(&graph, 3, 2, 20);
    addEdge(&graph, 3, 4, 60);

printf("Dijkstra's algorithm:\n");
dijkstra(&graph, 0);

printf("\n");

printf("Floyd's algorithm:\n");
floyd(&graph);

return 0;

}