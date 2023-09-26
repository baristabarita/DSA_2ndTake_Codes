#include <stdio.h>
#include<stdlib.h>

#define MAX 5 
#define INF 200

typedef int Matrix[MAX][MAX];
typedef int Vertex;
typedef Vertex Set[MAX];

int* Dijkstra(Matrix * M, Vertex v);
void main(){
    Matrix graph = {
        {INF, 10, INF, 30, 100},
        {INF, INF, 50, INF, INF},
        {20, INF, INF, INF, 10},
        {INF, INF, 20, INF, 60},
        {INF, INF, INF, INF, INF}
    };
    int* SPF = Dijkstra(graph, 0);
    displayDijkstra(SPF);
}

int* Dijkstra(Matrix* M, Vertex v){
    int* path = malloc(sizeof(int)*MAX);
    int cost[MAX];
    int visited[MAX] = {0,0,0,0,0};
    int x, y, minCost, minV, Scount = 0;
    path[0] = v;
    for (x = 0; x < MAX; x++){ //Copy first the initial Distances from Vertex v
        cost[x] = (*M)[v][x];
    }
    cost[v] = 0;
    minCost = INF;
    minV = -1;

    while(Scount < MAX){
            for (x = 0; x < MAX; x++){  //gets the minimum Cost Vertex from the Unvisited Nodes
                if (visited[x] != 1 && cost[x] < minCost){
                    minCost = cost[x];
                    minV = x;
                    }
            }
                path[Scount++] = minV;
                visited[minV] = 1;

            if (minV != -1){
                for (x = 0; x < MAX; x++){ //Relaxation / Updates the SPF if there is any from the minV
                if ((*M)[minV][x] + cost[minV] < cost[x]){
                    cost[x] = (*M)[minV][x] + cost[minV];
                }
            }
            }
        minCost = INF;
        minV = -1;
    }

    printf("Cost: \n");
    for (x = 0 ; x < MAX; x++){
        printf("Vertex [%d] : %d\n", x, cost[x]);
    }
    printf("\n");
    return path;
    
}

void displayDijkstra(int *path){
    int x;
    printf("Path of Dijkstra: \n");
    for (x = 0; x < MAX; x++){
        printf("%d ", path[x]);
    }
    printf("\n");
}