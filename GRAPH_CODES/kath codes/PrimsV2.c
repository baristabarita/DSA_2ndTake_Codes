#include<stdio.h>
#include<stdlib.h>
#define SIZE 6

typedef struct node{
    int weight;
    int label;
    struct node*link;
}point,*ptr;

typedef ptr Graph[SIZE];

int Prim(Graph,int [],int);
void display(int []);
void initialize(Graph A);
void populate(Graph A);
void insert(Graph A,int parent,int child,int weight);

void main(){
    Graph A;
    initialize(A);
    populate(A);
    int V[]={0,1,2,3,4,5};
    printf("%d",Prim(A,V,0));
}

void initialize(Graph A){
    int x;
    for(x=0;x<SIZE;x++){
        A[x]=NULL;
    }
}

void populate(Graph A){
    insert(A,0,1,1);
    insert(A,0,2,5);
    insert(A,0,3,4);
    insert(A,0,4,6);
    insert(A,0,5,5);
    insert(A,1,0,1);
    insert(A,1,2,5);
    insert(A,1,5,6);
    insert(A,2,0,5);
    insert(A,2,1,5);
    insert(A,2,3,2);
    insert(A,3,0,4);
    insert(A,3,2,2);
    insert(A,3,4,1);
    insert(A,4,0,6);
    insert(A,4,3,1);
    insert(A,4,5,3);
    insert(A,5,0,5);
    insert(A,5,1,6);
    insert(A,5,4,3);
}

void insert(Graph A,int parent,int child,int weight){
    int x;
    ptr *trav;
    for(trav=&A[parent];*trav!=NULL;trav=&(*trav)->link){}
    if(*trav==NULL){
        *trav=(ptr)malloc(sizeof(struct node));
        if(*trav!=NULL){
            (*trav)->weight=weight;
            (*trav)->label=child;
            (*trav)->link=NULL;
        }
    }
}

int Prim(Graph A,int V[],int start){
    int U[SIZE],a,b,c,d,count=0,min,cost=0;
    
    ptr trav;
    U[count++]=start;
    while(count!=SIZE){
        min=999;
        for(a=0;a<SIZE;a++){
            for(c=0;c<count && V[a]!=U[c];c++){}
            if(c==count){
                for(b=0;b<count;b++){
                    for(trav=A[U[b]];trav!=NULL && trav->label!=V[a];trav=trav->link){}
                    if(trav!=NULL){
                        if(trav->weight < min){
                            d=V[a];
                            min=trav->weight;
                        }
                    }
                }
            }
        }
        printf("%d\n",min);
        cost +=min;
        U[count++]=d;
        
        
    }
    return cost;
}