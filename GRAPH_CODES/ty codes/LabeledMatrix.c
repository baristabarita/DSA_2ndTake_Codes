#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INFINITY 999
#define MAX 5

typedef enum {FALSE, TRUE} boolean;

typedef struct{
    int numNodes;
    int** edges;
}Graph;

void initializeGraph(Graph *gptr,int size){
    int row, col;
    gptr->numNodes=size;
    gptr->edges = (int**)malloc(sizeof(int*)*gptr->numNodes);
    if(gptr->edges!=NULL){
      for(row = 0;size>row;row++){
        gptr->edges[row] = (int*)malloc(sizeof(int)*size);
        for(col = 0;col<size;col++){
          gptr->edges[row][col] = INFINITY;
        }
      }   
    }

}

void displayGraphBackEnd(Graph gcpy){
    int row,col;
    printf("This is your Labeled Matrix Graph:\n");
    for(row = 0;row<gcpy.numNodes;row++){
        for(col = 0;col<gcpy.numNodes;col++){
            printf("\t%d",gcpy.edges[row][col]);
        }
        printf("\n");
    }
}

void displayGraph(int** graph,Graph gcpy){
    int row,col;
    printf("This is your Labeled Matrix Graph:\n");
    for(row = 0;row<gcpy.numNodes;row++){
        for(col = 0;col<gcpy.numNodes;col++){
            printf("\t%d",graph[row][col]);
        }
        printf("\n");
    }
}

void insertArc(Graph* gptr,unsigned int from,unsigned int to,int value){
    if(gptr->edges[from][to]==INFINITY){
        gptr->edges[from][to] = value;
    }
}

int minDist(Graph gptr,boolean visited[],int spcheck[]){
    int retval_index, temp, minval=INFINITY;
    for(temp=0;temp<gptr.numNodes;temp++){
        if(visited[temp]!=TRUE&&spcheck[temp]<minval){
            minval=spcheck[temp];
            retval_index=temp;
        }
    }
    return retval_index;
}

void printDisCost(Graph gcpy,int dist[]){
    int i;
    printf("Source\tCost\n");
    for(i=0;i<gcpy.numNodes;i++){
        printf("%d\t%d\n",i,dist[i]);
    }
}

void Dijkstra(Graph* gptr, int source){
    //Source address is set at 0 for default. Will add changes to parameters later.
    //Legend: 
    //x = Traverses through D array
    //w = Index of the minimum cost per loop/iteration
    //v = Index of D array to compare with smallest value plus nest path
	//i = Used to initialize the path and set
	//*D = 1D array that holds the path for source index
	//*V = Set that shows which nodes are visited 
    int x,w,v,i,*D;
    boolean *V;
    
    D=(int*)malloc(sizeof(int)*gptr->numNodes);
    V=(boolean*)malloc(sizeof(boolean)*gptr->numNodes);
    
    //Initializiation section of the fucnction
    for(i=0;i<gptr->numNodes;i++){
    	//Values in D are the values at Source Edge paths.
        D[i]=gptr->edges[source][i];
        V[i]=FALSE;
    }
    //Initializing Source Node to 0 cost and marking it as Visited
    D[source]=0;
    V[source]=TRUE;
    //Allows the function to loop through all instances 
    for(x=0;x<gptr->numNodes;x++){
    	//Uses the function to find the index of D with the smallest cost
        w = minDist(*gptr,V,D);
        //Sets D[w] as visited
        V[w]=TRUE;
        //Loop to compare the current D cost to the cost of min D value + cost of path from minimum to the current node.
        for(v=0;v<gptr->numNodes;v++){
        	//Because this set is Bitvector, only non visited nodes are compared
            if(V[v]!=TRUE){
                D[v]=(D[w]+gptr->edges[w][v]<D[v])?D[w]+gptr->edges[w][v]:D[v];
            }
        }
    }
    //Shows resulting array
    //Note: can have return value
    printDisCost(*gptr,D);
}

int** Floyd(Graph* gptr){
    int **D,w,v,k,x,row,col;
    boolean **V;
    D=(int**)malloc(sizeof(int*)*gptr->numNodes);
    V=(boolean**)malloc(sizeof(boolean*)*gptr->numNodes);
    for(row=0;row<gptr->numNodes;row++){
        D[row]=(int*)malloc(sizeof(int)*gptr->numNodes);
        V[row]=(boolean*)malloc(sizeof(boolean)*gptr->numNodes);
        for(col=0;col<gptr->numNodes;col++){
            D[row][col]=gptr->edges[row][col];
            V[row][col]=FALSE;
        }
    }
    for(k=0;k<gptr->numNodes;k++){
    	V[k][k]=TRUE;
    	D[k][k]=0;
        for(x=0;x<gptr->numNodes;x++){
            w=minDist(*gptr,V[k],D[k]);
            V[k][w]=TRUE;
            for(v=0;v<gptr->numNodes;v++){
                if(V[k][v]!=TRUE){
                    D[k][v]=(gptr->edges[w][v]+D[k][w]<D[k][v])?gptr->edges[w][v]+D[k][w]:D[k][v];
                }
            }
        }
	}
    displayGraph(D,*gptr);
    return D;
}

int getGraphCenter(int** cent){
	int retval=INFINITY,row,col,maxcol,*center_arr;
	center_arr=(int*)malloc(sizeof(int)*MAX);
	//First loop to collect all largest arc cost in each column
	for(col=0;col<MAX;col++){
		maxcol=0;
		for(row=0;row<MAX;row++){
			if(cent[row][col]>maxcol){
				maxcol=cent[row][col];
			}
		}
		center_arr[col]=maxcol;
	}
	//Second loop to locate the minimum cost in each max columns
	for(col=0;col<MAX;col++){
		if(center_arr[col]<retval){
			retval=center_arr[col];
		}
	}
	return retval;
}

int main(){
    Graph newGraph;
    initializeGraph(&newGraph,MAX);
    displayGraphBackEnd(newGraph);
    insertArc(&newGraph,0,1,10);
    insertArc(&newGraph,0,3,12);
    insertArc(&newGraph,2,1,7);
    insertArc(&newGraph,4,3,11);
    insertArc(&newGraph,1,2,3);
    insertArc(&newGraph,3,2,5);
    insertArc(&newGraph,2,4,9);
    insertArc(&newGraph,4,0,4);
    displayGraphBackEnd(newGraph);
    Dijkstra(&newGraph,2);
    
    int** catcher= Floyd(&newGraph);
    int catcher1 = getGraphCenter(catcher);
    printf("%d",catcher1);
}
