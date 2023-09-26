#include <stdio.h>
#define MAX 6

typedef struct {
char data;
int link;
}Nodetype;

typedef struct{
Nodetype Nodes[MAX];
int avail;
}VirtualHeap;

typedef int List;
VirtualHeap VH;
List L;

void insertFirst(VirtualHeap *VH, List *L,char elem){
    List new = (List)allocSpace(VH);
    if (new != -1){
        VH->Nodes[new].data = elem;
        VH->Nodes[new].link = *L;
        *L = new;
    }
      VH->avail++;
}

int allocSpace(VirtualHeap *VH)
{
    int avail = VH->avail;
    int link = VH->Nodes[avail].link;
    if (link == -1)
    {
        return -1;
    }
    VH->avail = link;
    VH->Nodes[avail].link = -1;
    VH->avail = avail;
    return avail;
}

void initVirtualHeap(VirtualHeap VH){
int x;
VH.avail = 0;
    for (x = 1; x < MAX; x++){
        VH.Nodes[x-1].link = x;
    }
    VH.Nodes[MAX].link=-1;
}

void display(VirtualHeap VH){
    for (int x = 0; x < MAX;x++){
        printf("%c",VH.Nodes[x]);
        VH.Nodes[x].link=VH.Nodes[x].link;
    }
}

void main(){
    initVirtualHeap(VH);
    insertFirst(&VH,&L,'A');
    insertFirst(&VH,&L,'B');
    insertFirst(&VH,&L,'C');
    insertFirst(&VH,&L,'D');
    display(VH);
}