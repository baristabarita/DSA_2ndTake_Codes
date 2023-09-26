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

typedef struct{
	int u,v;
	int cost;
}edge;

typedef struct{
	int vertices[MAX];
	int num_nodes;
}Tree;

typedef struct{
	int que_arr[MAX];
	int front,back,num_val;
}Queue;

typedef struct node{
	int to_node;
	struct node* next;
}Node;

typedef struct{
	Node comp_arr[MAX];
}Component;

//Global Initialization
Tree ret={-1,-1,-1,-1,-1};

void initializeGraph(Graph* gptr){
	int row,col;
	gptr->numNodes = MAX;
	gptr->edges = (int**)malloc(sizeof(int*)*MAX);
	for(row=0;row<MAX;row++){
		gptr->edges[row]=(int*)malloc(sizeof(int)*MAX);
		for(col=0;col<MAX;col++){
			gptr->edges[row][col]=(row==col)?0:INFINITY;
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

void insertArc(Graph* gptr,int from,int to,int value){
	if(gptr->edges[from][to]==INFINITY){
		gptr->edges[from][to]=value;
		gptr->edges[to][from]=value;
	}
}

//int Prims(Graph* gptr){
//    int u,v,count,mincost,min_v=-1,min_set=-1,retval=0,temp;
//    int set[MAX]={0};
//    edge e[MAX]={-1};
//    count=0;
//    while(count<MAX-1){
//        mincost=INFINITY;
//        for(u=0;u<=count;u++){
//            for(v=0;v<MAX;v++){
//                if(gptr->edges[set[u]][v]<mincost&&set[u]!=v){
//                  	for(temp=0;temp<=count&&e[temp].u!=set[u]&&e[temp].v!=v;temp++){
//                      mincost=e[temp].cost=gptr->edges[set[u]][v];
//                      min_set=e[temp].u=set[u];
//                      min_v=e[temp].v=v;
//                  	}  
//                }
//            }
//        }
//        e[count].u=min_set;
//        e[count].v=min_v;
//        set[++count]=min_v;
//        retval+=e[count].cost=mincost;
//    }
//    return retval;
//}

int Prims(Graph* gptr){
	//Initialization of all used variables
	int x,y,retval=0,min_u,min_v,mincost,edge_num=0;
	//Visited array is an array of boolean values that represent if a node is already visited.
	boolean visited_arr[MAX]={FALSE};
	//Sets source node into True.
	//Note: The source node can be changed if parameter list allows it.
	visited_arr[0]=TRUE;
	//This is a list of edges used for Prim's Algorithm.
	edge temp[MAX-1]={0};
	
	while(edge_num<MAX-1){
		mincost=INFINITY;
		min_v=min_u=0;
		for(x=0;x<MAX;x++){
			if(visited_arr[x]==TRUE){
				for(y=0;y<MAX;y++){
					if(visited_arr[y]==FALSE&&gptr->edges[x][y]<mincost){
						mincost=gptr->edges[x][y];
						min_u=x;
						min_v=y;
					}
				}
			}
		}
		temp[edge_num].cost=retval+=mincost;
		temp[edge_num].v=min_v;
		temp[edge_num].u=min_u;
		visited_arr[min_v]=TRUE;
		edge_num++;
	}

	return retval;
}

void insertToComp(Component* cptr){
	
}

//boolean isComp(Component ccpy,int from_node){
//	int temp;
//	Node trav;
//	for(trav=ccpy.comp_arr[from_node];trav!=NULL;trav=trav.next){}
//	return temp;
//}

int Kruskal(Graph* gptr){
	//Initialization of all used variables
	int x,y,min_u=0,min_v=0,mincost,retval=0,components=MAX;
	boolean visited_arr[MAX]={FALSE};
	edge temp[MAX-1]={0};
	while(components>1){
		temp[components].u=min_u;
		temp[components].v=min_v;
		mincost=INFINITY;
		min_u = min_v=0;
		for(x=0;x<MAX;x++){
			for(y=x+1;y<MAX;y++){
				if(x!=temp[components].u&&y!=temp[components].v&&gptr->edges[x][y]<mincost){
					mincost=gptr->edges[x][y];
					min_u=x;
					min_v=y;
				}
			}
		}
		retval=temp[components].cost+=mincost;
		components--;
	}
	return retval;
}

void insertTree(Tree* tptr,int par,int child){
	int temp,free;
	if(tptr->vertices[0]==-1){
		tptr->vertices[0] = par;	
	}
	for(temp=0;temp<MAX&&tptr->vertices[temp]==par;temp++){}
	free=(tptr->vertices[temp*2+1]==-1)?temp*2+1:temp*2+2;
	tptr->vertices[free]=child;
}

void displayTree(Tree tcpy){
	int temp;
	printf("Tree Array Result: \n");
	for(temp=0;temp<MAX;temp++){
		printf("%d ->",tcpy.vertices[temp]);
	}
	printf("\n");
}

void ENQUEUE(Queue* qptr,int node){
	qptr->num_val++;
	qptr->que_arr[++qptr->back]=node;
}

void DEQUEUE(Queue* qptr,int node){
	qptr->num_val--;
	qptr->front++;
}

void BFS(Graph* gptr){
    int x,y;
    boolean mark[MAX];
    Queue visited;
    //Initializing Queue into chosen vertex
    visited.que_arr[MAX]=0;
    visited.back=-1;
    visited.front=0;
    visited.num_val=1;
    //Initialize mark using bit-vector datatype
    int temp;
    for(temp=0;temp<MAX;temp++){
        mark[temp]=FALSE;
    }
    
    mark[0]=TRUE;
    ENQUEUE(&visited,0);
    while(visited.num_val!=0){
         x=visited.que_arr[visited.front];
         DEQUEUE(&visited,visited.front);
         if(visited.num_val!=0){
           for(y=0;y<MAX;y++){
             	if(gptr->edges[x][y]!=INFINITY&&mark[y]==FALSE){
                 	mark[y]=TRUE;
                 	ENQUEUE(&visited,y);
                 	insertTree(&ret,x,y);
             	}
         	}
        }   
    }    
}

void DFS(Graph* gptr, boolean* mark_add){
	int temp,x,y;
	mark_add[0]=TRUE;
	for(x=0;x<MAX;x++){
		for(y=0;y<MAX;y++){
			if(gptr->edges[x][y]!=INFINITY&&mark_add[y]==FALSE){
				mark_add[y]=TRUE;
				insertTree(&ret,x,y);
				DFS(gptr,mark_add);
			}
		}
	}  
}

void initializeTree(Tree* tptr){
	int x;
	for(x=0;x<MAX;x++){
		tptr->vertices[x]=-1;
	}
	tptr->num_nodes;
}

int main(){
	Graph test;
	initializeGraph(&test);
	displayGraphBackEnd(test);
	
	insertArc(&test,4,1,10);
	insertArc(&test,2,4,15);
	insertArc(&test,3,1,12);
	insertArc(&test,2,3,9);
	insertArc(&test,1,2,5);
	insertArc(&test,1,0,14);
	insertArc(&test,0,4,3);
	
	Tree newtree;
	initializeTree(&newtree);
	
	displayGraphBackEnd(test);
	int mincost=Prims(&test);
	printf("Minimum Cost of Prim's Algoritm : %d\n",mincost);
	
	int temp;
	boolean* mark;
	mark = (boolean*)malloc(sizeof(boolean)*MAX);
	//Initialize marked array
	for(temp=0;temp<MAX;temp++){
		mark[temp]=FALSE;
	}
	
	BFS(&test);
	displayTree(ret);
}
