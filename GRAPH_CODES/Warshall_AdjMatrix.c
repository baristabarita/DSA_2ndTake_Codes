#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define INF 999
#define SIZE 5

typedef int Graph[SIZE][SIZE];

void Warshall(Graph A, Graph C);
void display(Graph G);


void main(){
    Graph A = {
              {1,1,1,1,1},
              {0,1,1,1,0},
              {0,0,1,0,1},
              {0,1,0,1,1},
              {0,0,1,1,1}
              };

    Graph B;
    printf("\n***** Before Warshall *****\n");
    display(A);

    Warshall(B, A);
    
    printf("\n***** After Warshall *****\n");
    display(B);
}

void Warshall(Graph A, Graph C){
    int i, j, k;

    /*
    for(i = 0; i < SIZE; i++){
        for(j = 0; j < SIZE; j++){
            A[i][j] = C[i][j];
        }
    }
    */
    //or
    memcpy(A,C,sizeof(int)*SIZE*SIZE);
    for(k = 0; k < SIZE; k++){
        for(i = 0; i < SIZE; i++){
            for(j = 0; j < SIZE; j++){
                if(A[i][j] == 0){
                    A[i][j] = A[i][k] && A[k][j];
                }
            }
        }
    }
}
void display(Graph G){
    int i, j;
    for(i = 0; i < SIZE; i++){
        for(j = 0; j < SIZE; j++){
            printf("%7d",G[i][j]);
        }
        printf("\n");
    }
}


