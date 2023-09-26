#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SIZE 5

typedef int Graph[SIZE][SIZE];

void Warshall(Graph,Graph);
void displayGraph(Graph);

void main(){
	Graph A ={
			 {1,1,1,1,1},
			 {0,1,1,1,1},
			 {0,1,1,1,1},
			 {0,0,1,1,1},
			 {0,0,1,1,1},
			 };
	Graph B;
	Warshall(B,A);	 
	displayGraph(B);	
}

void Warshall(Graph A,Graph C){
	int i,j,k;
	
	memcpy(A,C,sizeof(int)*SIZE*SIZE); 
	/* Can use
	  for(i=0;i<SIZE;i++)
	  for(j=0;j<SIZE;j++)
	*/
	
	for(k=0;k<SIZE;k++){
		for(i=0;i<SIZE;i++){
			for(j=0;j<SIZE;j++){
				if(A[i][j]==0){
					A[i][j] = A[i][k] && A[k][j];
				}
			}
		}
	}
}

void displayGraph(Graph G){
    int x, y;
    for(x=0; x<SIZE; x++){
        for(y=0; y<SIZE; y++){
            printf("%d ", G[x][y]);
        }
        printf("\n");
    }
}