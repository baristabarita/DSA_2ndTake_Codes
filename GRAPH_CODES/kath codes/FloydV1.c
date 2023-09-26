#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 101
#define SIZE 5

typedef int Graph[SIZE][SIZE];

void Floyd(Graph,Graph);
void display(Graph);
void populate(Graph);
void initialize(Graph);
int findCenter(Graph);

void main(){
	Graph C,A;
	initialize(C);
	populate(C);
	Floyd(A,C);
	display(A);
	printf("\nCenter of Graph: %d",findCenter(A));
}

void display(Graph A){
	int x,j;
	for(x=0;x<SIZE;x++){
		for(j=0;j<SIZE;j++){
			printf("%d\t",A[x][j]);
		}
		printf("\n");
	}
}

void initialize(Graph A){
	int x,j;
	for(x=0;x<SIZE;x++){
		for(j=0;j<SIZE;j++){
			A[x][j]=MAX;
		}
	}
}

void populate(Graph A){
	A[0][1]=10;
	A[0][3]=30;
	A[0][4]=100;
	A[1][2]=50;
	A[2][0]=20;
	A[2][4]=10;
	A[3][2]=20;
	A[3][4]=60;
}

void Floyd(Graph A,Graph C){
	int i,j,k;
	memcpy(A,C,sizeof(int)*SIZE*SIZE);
	
	for(i=0;i<SIZE;i++){
		A[i][i]=0;
	}
	
	for(k=0;k<SIZE;k++){
		for(i=0;i<SIZE;i++){
			for(j=0;j<SIZE;j++){
				if(A[i][k] + A[k][j] < A[i][j]){
					A[i][j] = A[i][k] + A[k][j];
				}
			}
		}
	}
}

int findCenter(Graph A){
  int max, x, y;
  int ecc[SIZE];
  for(y=0; y<SIZE; y++){
    max = A[0][y];
    for(x=1; x<SIZE; x++){
      max = (max>A[x][y])? max : A[x][y];
    }
    ecc[y] = max;
  }
  max = 0;
  for(x=1; x<SIZE; x++){
    max = (ecc[max]<ecc[x])? max : x;
  }
  return max;
}
