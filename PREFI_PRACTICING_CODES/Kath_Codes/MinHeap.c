#include<stdio.h>
#include<stdlib.h>
#define SIZE 10

typedef struct{
	int Elem[SIZE];
	int lastNdx;	
}HeapList;

void initialize(HeapList*);
void insert(HeapList*,int elem);
void minSubHeapify(HeapList*,int); /*To be used at heapify and deleteMin*/
void minHeapify(HeapList*);
int deleteMin(HeapList*);
void minHeapSort(HeapList*);

void displayArr(HeapList);

void main(){
	int i,oldLast;
	printf("\n-->Unsorted List");
	HeapList L={{5,1,8,2,9,1,7,2,3},8};
	
	/*oldLast=L.lastNdx;
	initialize(&L);
	for(i=0;i<=oldLast;i++){
		insert(&L,L.Elem[i]);
	}*/
	displayArr(L);
	
	printf("\n-->Heapify");
	minHeapify(&L);
	displayArr(L);

	printf("\n-->Sorted List");	
	minHeapSort(&L);
	displayArr(L);
}

void initialize(HeapList*L){
	L->lastNdx=-1;
}

int deleteMin(HeapList*H){
	int ret;
	if(H->lastNdx!=-1){
		ret=H->Elem[0];
		H->Elem[0]=H->Elem[H->lastNdx];
		H->lastNdx--;
		minSubHeapify(H,0);
	}
	return ret;
}

void minHeapSort(HeapList*H){
	int min,oldNdx = H->lastNdx;
	while(H->lastNdx!=-1){
		min=deleteMin(H);
		H->Elem[H->lastNdx+1]=min;
	}	
	H->lastNdx=oldNdx;
}

void minSubHeapify(HeapList*H,int parent){
	int LC,RC,SC,temp,old;
	LC=parent * 2 + 1;
	RC=parent * 2 + 2;
	SC = H->Elem[LC] < H->Elem[RC] ? LC : RC;
	while((LC<=H->lastNdx) && H->Elem[parent] > H->Elem[SC]){
		temp=H->Elem[parent];
		H->Elem[parent]=H->Elem[SC];
		H->Elem[SC]=temp;
		parent=SC;
		LC=parent * 2 + 1;
		SC = H->Elem[LC] < H->Elem[LC+1] ? LC : LC+1;
	}
}

void minHeapify(HeapList*H){
	int parent;
	for(parent=(H->lastNdx-1)/2;parent>=0;parent--){
		minSubHeapify(H,parent);
	}
}

void insert(HeapList*H,int elem){
	int parent,temp,indx;
	if(H->lastNdx!=SIZE-1){
		++H->lastNdx;
		H->Elem[H->lastNdx]=elem;
		indx=H->lastNdx;
		parent=(indx-1)/2;
		while(indx>0 && H->Elem[parent] > H->Elem[indx]){
			temp=H->Elem[parent];
			H->Elem[parent]=H->Elem[indx];
			H->Elem[indx]=temp;
			indx=parent;
			parent=(indx-1)/2;
		}
	}
}

void displayArr(HeapList H){
	int x;
	if(H.lastNdx!=-1){
		printf("\nDisplaying Array | ");
		for(x=0;x<=H.lastNdx;x++){
			printf("%d ",H.Elem[x]);
		}
	}else{
		printf("\nHeap is Empty");
	}
	printf("\n");
}