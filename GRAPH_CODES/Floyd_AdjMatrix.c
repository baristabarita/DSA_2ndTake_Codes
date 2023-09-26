#include<stdio.h>
#include<stdlib.h>

#define INF 999
#define SIZE 5

typedef int Graph[SIZE][SIZE];

void initialize(Graph G);
void display(Graph G);
void populate(Graph G);
void Floyd(Graph A, Graph C);
int FindCenter(Graph A);

void main(){
    Graph A, C;
    printf("\n**** Initialization of Graph ****\n");
    initialize(C);
    display(C);
    printf("\n**** Populating Graph ****\n");
    populate(C);
    display(C);
    printf("\n**** Graph after Floyd's Algorithm ****\n"); 
    Floyd(A, C);
    display(A);
    printf("\n Center of the Graph: %d", FindCenter(A));
}

void initialize(Graph G){
    int i, j;
    for(i = 0; i < SIZE; i++){
        for(j = 0; j < SIZE; j++){
            G[i][j] = INF;
        }
    }
}
void display(Graph G){
    int i, j;
    for(i = 0; i < SIZE; i++){
        for(j = 0; j < SIZE; j++){
            printf("\t%d", G[i][j]);
        }
        printf("\n");
    }
}
void populate(Graph G){
    G[0][1]=10;
	G[0][3]=30;
	G[0][4]=100;
	G[1][2]=50;
	G[2][0]=20;
	G[2][4]=10;
	G[3][2]=20;
	G[3][4]=60;
}

void Floyd(Graph A, Graph C){
    //Graph A is the shortest path from any source vertex to any destination vertext will be stored
    //Graph C is the labeled Adj. Matrix
    
    int i, j, k;

    //copies the labeled adj matrix to A (can be doen using memcpy)
    for(i = 0; i < SIZE; i++){
        for(j = 0; j < SIZE; j++){
            A[i][j] = C[i][j];
        }
    }

    //sets the diagonal to zero
    for(i = 0; i < SIZE; i++){
        A[i][i] = 0;
    }

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

int FindCenter(Graph A){
    //x is the row, y is the column

    int max, x, y;
    int ecc[SIZE];
    for(y = 0; y < SIZE; y++){
        max = A[0][y];
        for(x = 1; x < SIZE; x++){
            max = (max > A[x][y])? max : A[x][y];
        }
        ecc[y] = max;
    }
    max = 0;
    for(x = 1; x < SIZE; x++){
        max = (ecc[max] < ecc[x])? max : x;
    }
    return max;
}