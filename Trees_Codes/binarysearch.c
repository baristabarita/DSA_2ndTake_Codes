#include<stdio.h>

#define SIZE 30

typedef struct{
    int Elem[SIZE];
    int count; //actual # of elements in the array;
}LIST;

int findElem(LIST L, int x);

void main(){
    LIST L = {{10, 20, 30, 40, 50, 60, 80, 90, 100, 105, 110, 120}, 12};
    printf("%d", findElem(L, 105));
}

int findElem(LIST L, int x){
    int LB = 0;
    int UB = L.count - 1;
    int mid;

    while(LB <= UB && L.Elem[mid = ((LB+UB)/2)] != x){
        (L.Elem[mid] < x) ? (LB = mid+1) : (UB=mid-1);
    }
    return(LB <= UB && L.Elem[mid] == x) ? 1 : 0;
}