#include<stdio.h>
#include<stdlib.h>
#define MAX 101
#define SIZE 5
//#define UNVISITED -2
//#define VISITED -1

int * Dijkstra(int [][SIZE],int);
void display(int []);

void main(){
	int G[][SIZE]={
		{MAX,10,MAX,30,100},
		{MAX,MAX,50,MAX,MAX},
		{20,MAX,MAX,MAX,10},
		{MAX,MAX,20,MAX,60},
		{MAX,MAX,MAX,MAX,MAX},
	};
	
	int *nGraph=Dijkstra(G,0);
	display(nGraph);
}

void display(int A[]){
	int x;
	for(x=0;x<SIZE;x++){
		printf("%d ",A[x]);
	}
}

int * Dijkstra(int C[][SIZE],int startV){
	int *N, S[SIZE],Scount=0,x,y,i,w,min=69000;
	
	int V[SIZE]={0,1,2,3,4};
	N=(int*)malloc(sizeof(int)*SIZE);
	
	if(N!=NULL){
		S[0]=startV;
		++Scount;
		
		for(i=0;i<SIZE;i++){
			N[i]=C[startV][i];
		}
		
		for(i=1;i<SIZE;i++){
			for(x=0;x<SIZE;x++){
				for(y=0;y<Scount && V[x]!=S[y];y++){}
				if(y==Scount && N[V[x]]<min){
					min=N[V[x]];
					w=V[x];	
				}
			}
			
			S[Scount]=w;
			++Scount;
			for(x=0;x<5;x++){
				for(y=0;y<Scount && V[x]!=S[y];y++){}
					if(y==Scount){
						if(N[V[x]] > N[w] + C[w][V[x]]){
							N[V[x]]=N[w] + C[w][V[x]];
						}
					}
			}
			min=69000;
		}
	}
	return N;
}