#include<stdio.h>
#include<stdlib.h>
#define MAX 10

typedef struct{
	int Elem[MAX];
	int lastNdx;
}Heap;

void display(Heap);
void insert(Heap*H,int elem);
int LC(Heap,int);
int RC(Heap,int);
int deleteMin(Heap*);

void main(){
	Heap H;
	H.lastNdx=-1;
	int arr[]={3,4,9,6,5,9,10,10,18,7};
	int x,size;
	size=sizeof(arr)/sizeof(arr[0]);
	for(x=0;x<size;x++){
		insert(&H,arr[x]);
	}

	display(H);
	
	int num=0;
	printf("\n\nParent\t\tLC\t\tRC");
	for(;num<=H.lastNdx;num++){
	printf("\n%d\t\t%d\t\t%d",H.Elem[num],LC(H,num),RC(H,num));
	}
	
}

void insert(Heap*H,int elem){
	int parent,index;
	
	if(H->lastNdx<MAX-1){
	    ++H->lastNdx;
	    index=H->lastNdx;
	    parent=(index-1)/2;
	    while(index>0 && H->Elem[parent]>elem){
	    	H->Elem[index]=H->Elem[parent];
	    	index=parent;
	    	parent=(index-1)/2;
		}
		H->Elem[index]=elem;		
	}
}

int deleteMin(Heap*H){
	int ret=-1,trav,child,swap;
	if(H->lastNdx!=-1){
		ret=H->Elem[0];
		H->Elem[0]=H->Elem[H->lastNdx];
		--H->lastNdx;
		trav=0;
		child=1;
		
		while(child<=H->lastNdx){
			if(child<=H->lastNdx && H->Elem[child+1]<H->Elem[child]){
				child++;
			}
			
			if(H->Elem[trav]>H->Elem[child]){
				swap = H->Elem[trav];
				H->Elem[trav]=H->Elem[child];
				H->Elem[child]=swap;
				trav=child;
				child=trav*2+1;
			}else{
				break;
			}
		}
	}
	return ret;
}

int LC(Heap H,int pos){
	int ret=pos*2+1;
	return ret<MAX ? H.Elem[ret] : -1;
}

int RC(Heap H,int pos){
	int ret=pos*2+2;	
	return ret<MAX  ? H.Elem[ret] : -1;
}

void display(Heap H){
	int x;
	for(x=0;x<=H.lastNdx;x++){
		printf("%d\t",x);
	}
	printf("\n=============================================================================\n");
	for(x=0;x<=H.lastNdx;x++){
		if(H.Elem[x]>0){
		printf("%d\t", H.Elem[x]);
		}else{
			printf(" ");
		}
	}
}