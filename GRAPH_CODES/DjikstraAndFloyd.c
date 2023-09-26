

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERTICES 5
#define UNVISITED 0
#define VISITED 1
#define INF 999

typedef int Matrix[VERTICES][VERTICES];
typedef int Djikstra[VERTICES];

typedef struct item{
    int e;
    struct item* link;
}*Stack;
void initMatrix(int m[VERTICES][VERTICES]);
void displayMatrix(Matrix m);
int* Dijkstra (Matrix m, int Source);

void main(){
    Matrix m;
    initMatrix(m);
    //displayMatrix(m);
    int* SPF  = Dijkstra(m, 0);
    printf("\nDjiskta at Source V(0):\n");
    displayDijkstra(SPF);
    Matrix f;
    Floyd (m, f);
    printf("\nMATRIX\n");
    displayMatrix(m);
    printf("\nFLOYD\n");
    displayMatrix(f);
    
}

void initMatrix(int m[VERTICES][VERTICES]){
    int x, y;
    for (x = 0; x < VERTICES; x++){
        for (y = 0; y < VERTICES; y++)
            m[x][y] = INF;
    }
    
    m[0][4] = 100;
    m[0][3] = 30;
    m[0][1] = 10;
    m[1][2] = 50;
    m[2][0] = 20;
    m[2][4] = 10;
    m[3][2] = 30;
    m[3][4] = 60;
}

void displayDijkstra(int arr[]){
    int x = 0;
    for (x = 0; x < VERTICES; x++){
        printf("%d ", arr[x]);
    }
}

void displayMatrix(Matrix m){
        int x, y;
    for (x = 0; x < VERTICES; x++){
        for (y = 0; y < VERTICES; y++){
            printf("\t%d ", m[x][y]);
        }
            printf("\n");
    }
}

int* Dijkstra (Matrix m, int Source){
    int* D = calloc(sizeof(int),VERTICES);
    int *isVisited =  calloc(sizeof(int),VERTICES);
    int i, x, min = Source, idx;
    memcpy(D, m[Source], sizeof(int)*VERTICES);
    
    for (x = 0; x < VERTICES; x++){
        if (x != min){
        	idx = D[0];
            for (i = 0; i < VERTICES; i++){
                //printf("%d\n", m[min][i] + D[min]);
                if ((m[min][i] + D[min]) < D[i] ){
                    D[i] = m[min][i] + D[min];
                }
                if (idx > D[i] && isVisited[i] == UNVISITED){
                	idx = D[i];
                	min = i;
				}
                
            }
            isVisited[min] = VISITED;
        }else{
            isVisited[x] = VISITED;
        }
    }
    D[Source] = 0;
    return D;
}

void Floyd(Matrix m, Matrix D){
	
    int *isVisited;
    int i, x, min, Source, idx;
    memcpy(D, m, sizeof(int[VERTICES][VERTICES]));
    //displayMatrix(D);
    
    for (Source = 0 ;Source < VERTICES; Source++){
    	min = Source;
    	isVisited =  calloc(sizeof(int),VERTICES);
    for (x = 0; x < VERTICES; x++){
        if (x != min){
        	idx = D[Source][0];
            for (i = 0; i < VERTICES; i++){
                //printf("%d\n", m[min][i] + D[min]);
                if ((m[min][i] + D[Source][min]) < D[Source][i] ){
                    D[Source][i] = m[min][i] + D[Source][min];
                }
                if (idx > D[Source][i] && isVisited[i] == UNVISITED){
                	idx = D[Source][i];
                	min = i;
				}
                
            }
            isVisited[min] = VISITED;
        }else{
            isVisited[x] = VISITED;
        }
    }

    D[Source][Source] = 0;
    free(isVisited);
}
}

void initStack(Stack* S){
    *S = NULL;
}

void pushStack(Stack *S, int num){
    Stack temp = malloc(sizeof(struct item));
    if (temp!= NULL){
        temp->link = (*S);
        *S = temp;
    }
}

void showPath(Stack S, int num){
    Stack trav = S;
    while (trav!=NULL){
        printf("%d ", trav->e);
        if (trav->e == num){
            trav = NULL;
        }else{
            trav = trav->link;
            printf("----> ");
        }
    }
}
