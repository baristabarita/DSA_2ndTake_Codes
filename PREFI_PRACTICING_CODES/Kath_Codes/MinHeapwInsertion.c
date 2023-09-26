#include<stdio.h>
#include<stdlib.h>
#define SIZE 15
#define N 11

typedef struct{
	int Elem[SIZE];
	int lastNdx;	
}Heap;

void initialize(Heap*);
void insert(Heap*,int);
int deleteMin(Heap*);

/*Custom Functions*/
int LC(Heap,int);
int RC(Heap,int);
void HeapInsert(Heap*);
void minHeapSort(Heap*);

/*Custom Display*/
void preorder(Heap,int);
void inorder(Heap,int);
void postorder(Heap,int);
void displayAll(Heap,int);
void displayArr(Heap);

void main(){
	Heap H,A;
	int x;
	
	initialize(&H);
	printf("-->Initialize");
	displayArr(H);
	printf("\n-->Insert");
	int arr[N]={3,4,9,6,5,9,10,10,18,7,2};
	for(x=0;x<N;x++){
		insert(&H,arr[x]);
	}
	displayArr(H);
	displayAll(H,0);
	printf("\n\n-->DeleteMin\n");
	printf("Minimum Deleted: %d",deleteMin(&H));
	displayArr(H);
	displayAll(H,0);
	printf("\n\nLeft child of %d : %d",H.Elem[2],LC(H,2));
	printf("\nRight child of %d : %d",H.Elem[2],RC(H,2));
	
	/*Testing HeapSort*/
	Heap list={{5,1,8,2,9,1,7,2,3},8};
	HeapInsert(&list);
	displayArr(list);
	minHeapSort(&list);
	displayArr(list);
}

void initialize(Heap*H){
    H->lastNdx=-1;
}

void insert(Heap*H,int elem){
    int indx,temp,parent;
    if(H->lastNdx!=SIZE-1){
      H->lastNdx++;
      H->Elem[H->lastNdx]=elem;
      indx=H->lastNdx;
      parent=(indx-1)/2;
      while(H->Elem[parent] > H->Elem[indx]){
          temp=H->Elem[parent];
          H->Elem[parent]=H->Elem[indx];
          H->Elem[indx]=temp;
          indx=parent;
          parent=(indx-1)/2;
      }
    }
}

int deleteMin(Heap*H){
    int SC,LC,RC,temp,ret,parent;
    if(H->lastNdx!=-1){
        ret=H->Elem[0];
        H->Elem[0]=H->Elem[H->lastNdx];
        H->lastNdx--;
        parent=0;
        LC=parent*2+1;
        RC=parent*2+2;
        SC = H->Elem[LC] < H->Elem[RC] ? LC : RC;
        while(LC<=H->lastNdx && H->Elem[parent] > H->Elem[SC]){
            temp=H->Elem[parent];
            H->Elem[parent]=H->Elem[SC];
            H->Elem[SC]=temp;
            parent=SC;
            LC=parent*2+1;
            RC=parent*2+2;
            SC = H->Elem[LC] < H->Elem[RC] ? LC : RC;
        }
    }
    return ret;
}

/*Custom Functions*/
int LC(Heap H,int elem){
    int ret = elem * 2 + 1;
    return elem>=0 && elem<SIZE ? H.Elem[ret] : -1;
}
int RC(Heap H,int elem){
    int ret = elem * 2 + 2;
    return elem>=0 && elem<SIZE ? H.Elem[ret] : -1;
}

/*Inserts on an empty POT*/
void HeapInsert(Heap* H){
    int LC,SC,temp,x,oldNdx=H->lastNdx;

    H->lastNdx=-1;
    for(x=0;x<=oldNdx;x++){
        insert(H,H->Elem[x]);
    }
}

/*Turns to a sorted list in descending order*/
void minHeapSort(Heap*H){
	int min,oldNdx = H->lastNdx;
	while(H->lastNdx!=-1){
		min=deleteMin(H);
		H->Elem[H->lastNdx+1]=min;
	}	
	H->lastNdx=oldNdx;
}


/*Custom Display*/
void preorder(Heap H,int pos){
	int LC,RC;
	if(pos<=H.lastNdx && H.lastNdx!=SIZE-1){
		printf("%d ",H.Elem[pos]);
		LC=pos*2+1;
		preorder(H,LC);
		preorder(H,LC+1);
	}
}

void inorder(Heap H,int pos){
	int LC,RC;
	if(pos<=H.lastNdx && H.lastNdx!=SIZE-1){
		LC=pos*2+1;
		inorder(H,LC);
		printf("%d ",H.Elem[pos]);
		inorder(H,LC+1);
	}	
}
void postorder(Heap H,int pos){
	int LC,RC;
	if(pos<=H.lastNdx && H.lastNdx!=SIZE-1){
		LC=pos*2+1;
		postorder(H,LC);
		postorder(H,LC+1);
		printf("%d ",H.Elem[pos]);
	}	
}

void displayAll(Heap H,int pos){
	int x;
	if(H.lastNdx!=-1){
		printf("\nPreorder | ");
		preorder(H,pos);
		printf("\nInorder | ");
		inorder(H,pos);
		printf("\nPostorder | ");
		postorder(H,pos);
	}
}

void displayArr(Heap H){
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
