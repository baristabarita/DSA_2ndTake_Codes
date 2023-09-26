#include <stdio.h>
#include <stdlib.h>

#define INFINITY 999
#define SIZE 5

typedef int Graph[SIZE][SIZE];


void initGraph(Graph G);
void populate(Graph G);
void displayGraph(Graph G);
void displayDijk(int D[]);
int *Dijkstra(Graph G, int startV);


void main(){
    Graph G;
    printf("\n***** Graph Matrix After Initialization *****\n");
    initGraph(G);
    displayGraph(G);

    printf("\n***** Graph Matrix After Population *****\n");
    populate(G);
    displayGraph(G);
    
    int *dijk = Dijkstra(G, 0);
    displayDijk(dijk);
}

void initGraph(Graph G){
    int i, j;
    for(i = 0; i < SIZE; i++){
        for(j = 0; j < SIZE; j++){
            G[i][j] = INFINITY;
        }
    }
}
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

void displayGraph(Graph G){
    int i, j;
    for(i = 0; i < SIZE; i++){
        for(j = 0; j < SIZE; j++){
            printf("\t%d", G[i][j]);
        }
        printf("\n");
    }
}
int *Dijkstra(Graph G, int startV){
    int S[SIZE], i, j, x, sum = 0, w, Scount = 0, min = INFINITY;
    int V[SIZE] = {0, 1, 2 ,3 ,4};
    //int *D = (int*)malloc(sizeof(int)*SIZE);
    int *D = (int*)calloc(1,sizeof(int)*SIZE);

    if(D != NULL){
        S[Scount++] = startV;
        
        for(i = 1; i < SIZE; i++){
            D[i] = G[startV][i]; //Initializes D
        }
       
        for(i = 1; i < SIZE; i++){
             //A. Choose a vertex w in V-S such taht D[w] is a minimum (except source vertex)
            for(x = 0; x < SIZE; x++){
                for(j = 0; j < Scount && V[x] != S[j]; j++){}
                if(j == Scount && D[V[x]] < min){
                    min = D[V[x]];
                    w = V[x];
                }
            }
            //B. Add w to S
            S[Scount++] = w;
            //C. for each vertex w in V-S
            for(x = 0; x < SIZE; x++){
                for(j = 0; j < Scount && V[x] != S[j]; j++){}
                if(j == Scount){
                    sum = D[w] + G[w][V[x]];
                    D[V[x]] =( D[V[x]] < sum ) ? D[V[x]] : sum;
                }
            }
            min = INFINITY;
        }
    }
    return D;
}

void displayDijk(int D[]){
    int i, x;
    printf("Source\tCost\n");
    for(x = 0; x < SIZE; x++){
        printf("%d\t%d\n", x,D[x]);
    }
}