#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SIZE 5
#define MAX 101

typedef int Graph[SIZE][SIZE]; //Adjacency Matrix

void Floyd(Graph,Graph);
int findCenter(Graph);
void display(Graph);

void main(){
	Graph A = {
			{MAX,10,MAX,30,100},
			{MAX,MAX,50,MAX,MAX},
			{20,MAX,MAX,MAX,10},
			{MAX,MAX,20,MAX,60},
			{MAX,MAX,MAX,MAX,MAX},
			};
	
	Graph B;
	Floyd(B,A);
	display(B);
	printf("\nCenter of Graph: %d",findCenter(B));
}

void display(Graph A){
	int i,j;
	for(i=0;i<SIZE;i++){
		for(j=0;j<SIZE;j++){
			printf("%d\t",A[i][j]);
		}
		printf("\n");
	}
}

void Floyd(Graph Y,Graph Z){
	int a,b,c;
	
	memcpy(Y,Z,sizeof(int)*SIZE*SIZE);
	
	for(a=0;a<SIZE;a++){
		Y[a][a]=0;
	}
	
	for(c=0;c<SIZE;c++){
		for(a=0;a<SIZE;a++){
			for(b=0;b<SIZE;b++){
				if(Y[a][c] + Y[c][b] < Y[a][b]){
					Y[a][b] = Y[a][c] + Y[c][b];
				}
			}
		}
	}
}

int findCenter(Graph A){
	int max,Ecc[SIZE],center,a,b;
	
	for(a=0;a<SIZE;a++){
		max=A[0][a];
		for(b=1;b<SIZE;b++){
		    if(A[b][a] > max){
		    	max=A[b][a];
			}	
		}
		Ecc[a]=max;
	}
	
	center=Ecc[0];
	for(a=1;a<SIZE;a++){
		if(Ecc[a] < center){
			center=a;
		}
	}
	return center;
}