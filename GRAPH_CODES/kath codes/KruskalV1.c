#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 999
#define SIZE 6

typedef int Graph[SIZE][SIZE]; //Adjacency Matrix w/o labels

typedef struct{
	int vert[SIZE];
	int count;
}Vertex;

int kruskal(Graph,Vertex);
void initGraph(Graph);
void initV(Vertex*);
void display(Graph);
void populate(Graph);

void main(){
    Graph G;
    Vertex B;
    initGraph(G);
    initV(&B);
    
    populate(G);
    display(G);
    printf("\n\nMin Cost:%d \n", kruskal(G,B));	
}

int kruskal(Graph G,Vertex B){
	int a,b,prA,prB,min,cost=0;
	
	Graph T;
	
	memcpy(T,G,sizeof(Graph));
	prA=prB=0;
	while(B.count<SIZE-1){
		min=MAX;
		for(a=0;a<SIZE;a++){
			for(b=a+1;b<SIZE;b++){
				if(min > T[a][b]){
					min = T[a][b];
					prA=a;
					prB=b;
				}
			}
		}
		
		if(B.vert[prB]==-1 || B.vert[prA]==-1){
			if(B.vert[prA]==-1){
				B.vert[prB] = prA;
			}else{
				if(B.vert[prA]!=B.vert[prB]){
					B.vert[prB] = (B.vert[prA]!=-1) ? B.vert[prA] : prA;
				}
			}
			cost+=min;
			T[prA][prB] = T[prB][prA]=MAX;
			B.count++;
			
		}
	}
	return cost;
}

void initGraph(Graph G){
	int x,y;
	for(x=0;x<SIZE;x++){
		for(y=0;y<SIZE;y++){
			G[x][y]=MAX;
		}
	}
}

void initV(Vertex*V){
	int x;
	for(x=0;x<SIZE;x++){
		V->vert[x]=-1;
	}	
	V->count=0;
}

void display(Graph A){
	int x,y;
	for(x=0;x<SIZE;x++){
		for(y=0;y<SIZE;y++){
			printf("%5d ",A[x][y]);
		}
			printf("\n");
	}

}

void populate(Graph G){
    G[0][1] = G[1][0] = 1;
    G[0][2] = G[2][0] = 5;
    G[0][3] = G[3][0] = 4;
    G[0][4] = G[4][0] = 6;
    G[0][5] = G[5][0] = 5;
    G[1][2] = G[2][1] = 5;
    G[1][5] = G[5][1] = 6;
    G[2][3] = G[3][2] = 2;
    G[3][4] = G[4][3] = 1;
    G[4][5] = G[5][4] = 3;
}
