#include<stdio.h>
#include<stdlib.h>
#define SIZE 7
#define MAX 0
//can use any values,bit vector, or computer word for visited or unvisited
#define VISITED 'V'
#define UNVISITED 'U'

typedef int Graph[SIZE][SIZE];

struct{
	unsigned char vert[SIZE];
	int count;
}mark;

void initGraph(Graph);
void initMarked();
void dfs(Graph,int);

void main(){
	Graph A={{MAX,1,1,MAX,MAX,MAX,MAX},
	         {MAX,MAX,1,1,MAX,MAX,MAX},
	         {1,MAX,MAX,MAX,MAX,MAX,MAX},
	         {1,MAX,1,MAX,MAX,MAX,MAX},
	         {MAX,MAX,MAX,MAX,MAX,1,1},
	         {MAX,1,MAX,MAX,MAX,MAX,MAX},
	         {MAX,MAX,MAX,1,MAX,1,MAX},
	        };
	initMarked();
	dfs(A,4);
	if(mark.count<SIZE){
		dfs(A,mark.count);
	}
	
}
void initMarked(){
	int i;
	for(i=0;i<SIZE;i++){
		mark.vert[i]=UNVISITED;
	}
	mark.count=0;
}

void dfs(Graph A,int elem){
    int w;
    mark.vert[elem]=VISITED;
    mark.count++;
    printf("\nNode at %d",elem);
    for(w=0;w<SIZE;w++){
        if(A[elem][w]==1){
            if(mark.vert[w]==UNVISITED){
                dfs(A,w);
            }
        }
    }
}