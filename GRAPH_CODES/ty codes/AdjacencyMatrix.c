#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INFINITY 284709801324820

typedef enum {FALSE, TRUE} boolean;

typedef struct node{
	int numNodes;
	boolean **edges; 
}graph;

graph* createGraph(int size){
	int temp;
	graph *retval = (graph*)malloc(sizeof(graph));
	if(retval !=NULL){
		retval->numNodes = size;
		retval->edges = (boolean**)calloc(sizeof(boolean*),retval->numNodes);
		if(retval->edges != NULL){
			for(temp=0;temp<retval->numNodes;temp++){
				retval->edges[temp]=(boolean*)calloc(sizeof(boolean),retval->numNodes);
			}
		}
	}
	return retval;
}

void deleteGraph(graph* gptr){
	int temp;
	for(temp=0;temp<gptr->numNodes;temp++){
		free(gptr->edges[temp]);
	}
	free(gptr->edges);
	free(gptr);
}

void printBackEndGraph(graph* gptr){
	int row,col;
	printf("This is your graph with size %d:\n",gptr->numNodes);
	for(row=0;row<gptr->numNodes;row++){
		printf("\n");
		for(col=0;col<gptr->numNodes;col++){
			printf("%d\t",gptr->edges[row][col]);
		}
	}
}

void displayGraph(graph* gptr){
	int from, to;
	printf("\nGraph{\n");
	for(from = 0 ; from<gptr->numNodes;from++){
		for(to = 0; to<gptr->numNodes;to++){
			if(gptr->edges[from][to]==TRUE){
				printf("\t%d -> %d,\n",from,to);
			}
		}
	}
	printf("};");
}



boolean addEdge(graph* gptr, unsigned int fromNode,unsigned int toNode){
	boolean retval =  FALSE;
	if(gptr->edges[fromNode][toNode]!=TRUE){
		gptr->edges[fromNode][toNode] = TRUE;
		retval = TRUE;
	}
	return retval;
}

boolean isEdge(graph* gptr, unsigned int fromNode,unsigned int toNode){
	boolean retval = FALSE;
	if(gptr->edges[fromNode][toNode]==TRUE){
		retval = TRUE;
	}
	return retval;
}

void transitiveClosure(graph* gptr){
	int temp
	graph* trans = gptr;
	
}

int main (){
	graph* newGraph = createGraph(5);
	printBackEndGraph(newGraph);
	displayGraph(newGraph);
	addEdge(newGraph,2,4);
	addEdge(newGraph,1,0);
	addEdge(newGraph,3,1);
	addEdge(newGraph,2,1);
	addEdge(newGraph,1,4);
	printBackEndGraph(newGraph);
	displayGraph(newGraph);
	deleteGraph(newGraph);
}
