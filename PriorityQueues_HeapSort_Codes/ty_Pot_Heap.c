#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 15

typedef struct
{
    int elem[MAX];
    int last;
} Heap;

// Initializes heap to have -2 as empty values, might be used for later
void initHeap(Heap *hptr)
{
    int temp;
    for (temp = 0; temp < MAX; temp++)
    {
        hptr->elem[temp] = -2;
    }
    hptr->last = -1;
}

void displayHeap(Heap hptr)
{
    int temp;
    printf("There are the values inside the Heap:\n");
    for (temp = 0; temp < hptr.last + 1; temp++)
    {
        printf("%d    ", hptr.elem[temp]);
    }
    printf("\n");
}

// Common functions for Heap/POT
void InsertMin(Heap *hptr, int ins)
{
    // Legend:
    // temp = Variable will be for traversiall using last index of the heap
    // sw = Variable is for switching the values
    int temp, sw;
    // Creates space for new value
    temp = ++(hptr->last);
    // Places inserted value to the last index of the array;
    hptr->elem[temp] = ins;
    // Finds actual position in the heap
    // Stops when temp is
    while (temp > 0 && hptr->elem[temp] < hptr->elem[(temp - 1) / 2])
    {
        // Switch action
        sw = hptr->elem[temp];
        hptr->elem[temp] = hptr->elem[(temp - 1) / 2];
        hptr->elem[(temp - 1) / 2] = sw;
    }
}

// Technically the same as the InsertMin function
void InsertMax(Heap *hptr, int ins)
{
    int temp, sw;
    temp = ++(hptr->last);
    hptr->elem[temp] = ins;
    // Changed the sign from lesser than to a greater than
    while (temp > 0 && hptr->elem[temp] > hptr->elem[(temp - 1) / 2])
    {
        sw = hptr->elem[temp];
        hptr->elem[temp] = hptr->elem[(temp - 1) / 2];
        hptr->elem[(temp - 1) / 2] = sw;
    }
}
// Delete Functions
int deleteMin(Heap *hptr)
{
    // Legend:
    // trav = Varibale that holds the parent node for every iteration
    // sc = Small Child - will hold the index of the child that has a smaller value
    // min = The parent node that will be returned from the function. It is the smallest value
    int trav = 0, sc, min = hptr->elem[0];
    // The value at parent node gets replaced with the value at the last index
    hptr->elem[trav] = hptr->elem[hptr->last--];
    // This while loop will traverse through the HEAP if either the left child
    // node or the right child node is less than the last value.
    while (trav * 2 + 1 <= hptr->last || trav * 2 + 2 <= hptr->last)
    {
        // sc will accept the smaller value from the 2 children but the left child will
        // have priority over the right if the right child index(trav2*2+2) is greater than the last value.
        sc = (trav * 2 + 2 > hptr->last || hptr->elem[trav * 2 + 1] < hptr->elem[trav * 2 + 2]) ? trav * 2 + 1 : trav * 2 + 2;
        // The switch will only happen if the current parent(trav) is greater than the smaller child(sc).
        if (hptr->elem[trav] > hptr->elem[sc])
        {
            int temp = hptr->elem[trav];
            hptr->elem[trav] = hptr->elem[sc];
            hptr->elem[sc] = temp;
        }
        // Increment trav/parent node  into sc/child node
        trav = sc;
    }
    return min;
}
// Same process but signs are changed
int deleteMax(Heap *hptr)
{
    // bc = Bigger Child, holds the index of the bigger value
    int trav = 0, bc, max = hptr->elem[0];
    hptr->elem[trav] = hptr->elem[hptr->last--];
    while (trav * 2 + 1 <= hptr->last || trav * 2 + 2 <= hptr->last)
    {
        // Same principle as smaller child but accepts the index of the bigger value
        bc = (trav * 2 + 2 > hptr->last || hptr->elem[trav * 2 + 1] > hptr->elem[trav * 2 + 2]) ? trav * 2 + 1 : trav * 2 + 2;
        if (hptr->elem[trav] < hptr->elem[bc])
        {
            int temp = hptr->elem[trav];
            hptr->elem[trav] = hptr->elem[bc];
            hptr->elem[bc] = temp;
        }
        trav = bc;
    }
    return max;
}
// HeapSort
// Note: Probably optimizable but im ded rn so ye
void heapSortMin(Heap *hptr)
{
    // Legend:
    // trav = Will traverse through the current parent node
    // sc = finds the index of the smaller value
    // oldLast = holds the actual last index of the heap
    int trav = 0, sc, oldLast = hptr->last;
    // Not sure if this exit statement is correct for the while loop but trye replacinf it with "hptr->last>=0"
    // This is supposed to stop when the "Deletion" process ends in -1/deleted

    // Note: hptr->last will be used to limit the size of the heap as "Deletion" happens
    while (hptr->last >= 0)
    {
        // Switches the first and last node as of the current heap
        int sw = hptr->elem[trav];
        hptr->elem[trav] = hptr->elem[hptr->last];
        hptr->elem[hptr->last] = sw;
        // Removes the last index of the current heap and decreases size
        hptr->last--;
        // Loops/traverses from the current node to the last node
        // Will stop only if both indexes are not included in the current HEAP
        // This is technically deletion XD
        while (trav * 2 + 1 <= hptr->last || trav * 2 + 2 <= hptr->last)
        {
            // Finds the index of the smaller value
            sc = (trav * 2 + 2 > hptr->last || hptr->elem[trav * 2 + 1] < hptr->elem[trav * 2 + 2]) ? trav * 2 + 1 : trav * 2 + 2;
            // Will Switch only if the current parent node is bigger than the smaller child
            if (hptr->elem[trav] > hptr->elem[sc])
            {
                int temp = hptr->elem[trav];
                hptr->elem[trav] = hptr->elem[sc];
                hptr->elem[sc] = temp;
            }
            // Increment trav into sc node
            trav = sc;
        }
        // Sets the current node back to the parent node for the switch i.e. at index 0
        trav = 0;
    }
    // Once the loop ends, the value of hptr->last will be -1/deleted, oldLast will bring back the old size of
    // the HEAP.
    hptr->last = oldLast;
    return;
}

// Same process but different sizes
void heapSortMax(Heap *hptr)
{
    int trav = 0, bc, oldLast = hptr->last;
    while (hptr->last >= 0)
    {
        int sw = hptr->elem[trav];
        hptr->elem[trav] = hptr->elem[hptr->last];
        hptr->elem[hptr->last] = sw;
        hptr->last--;
        while (trav * 2 + 1 <= hptr->last || trav * 2 + 2 <= hptr->last)
        {
            // bs becomes the index of the biggest value of both children
            bc = (trav * 2 + 2 > hptr->last || hptr->elem[trav * 2 + 1] > hptr->elem[trav * 2 + 2]) ? trav * 2 + 1 : trav * 2 + 2;
            if (hptr->elem[trav] < hptr->elem[bc])
            {
                int temp = hptr->elem[trav];
                hptr->elem[trav] = hptr->elem[bc];
                hptr->elem[bc] = temp;
            }
            // Increment temp into bc node
            trav = bc;
        }
        trav = 0;
    }
    hptr->last = oldLast;
    return;
}
// Heap Normal Sorting Method

// Summary: this technically inserts each value of the area back to itself but in an POT form
void heapMin(Heap *hptr)
{
    // Legend:
    // oldLast = Holds the actual last index of the HEAP
    // trav = Traverses through the HEAP, acts like hptr->last
    // temp = will be used to traverse from the last node to the postion of the value it holds
    // sw = Used for switching values
    int oldLast = hptr->last, trav, temp;
    // Makes the HEAP empty
    hptr->last = -1;
    // You could just use hptr->last instead of trav and add hptr->last=oldLast; at the end of the function
    for (trav = 0; trav <= oldLast; trav++)
    {
        // temp will be at the last/added index of the current HEAP.
        temp = ++(hptr->last);
        // temp will move upward toward the root node or until it finds its actual position. That is where "temp>=0" comes
        while (temp >= 0 && hptr->elem[temp] < hptr->elem[(temp - 1) / 2])
        {
            // sw is used as a buffer for the switching of values
            int sw = hptr->elem[temp];
            hptr->elem[temp] = hptr->elem[(temp - 1) / 2];
            hptr->elem[(temp - 1) / 2] = sw;
            temp = (temp - 1) / 2;
        }
    }
    // Add the oldLast statement here if you won't use trav
}

// Heapify
// Fuck this shit took 2 hours to make
// Instead of inserting each node to the HEAP, this rearanges the values per parent node,
// starting formt the last parent to the root node.
void heapifyMin(Heap *hptr)
{
    // Legend:
    // pindex = This is the index of the last parent node.
    // sindex = This is the index of the smalles node of the current parent node.
    // temp = Simple switch variable.
    // in_pindex = This will be used to traverse the smaller indexes if the intial switch is not enough to
    // create the POT. This is the inner index.
    // in_sindex = This will hold the index of the smaller child of the inner parent node.
    int pindex = (hptr->last - 1) / 2, sindex, temp, in_pindex, in_sindex;
    // Will check if the pindex/parent node has reached the root node
    while (pindex >= 0)
    {
        // Sets the inner parent index as the currebt parenbt index
        in_pindex = pindex;
        // Sets sindex as the smaller child of the current parent node
        sindex = (pindex * 2 + 2 > hptr->last || hptr->elem[pindex * 2 + 1] < hptr->elem[pindex * 2 + 2]) ? pindex * 2 + 1 : pindex * 2 + 2;
        // Sames as pindex
        in_sindex = sindex;
        // This is the insertion process where the parent node traverses downwards
        while (in_pindex * 2 + 1 <= hptr->last || in_pindex * 2 + 2 <= hptr->last)
        {
            // Finds the current smaller child of the inner parent
            in_sindex = (in_pindex * 2 + 2 > hptr->last || hptr->elem[in_pindex * 2 + 1] < hptr->elem[in_pindex * 2 + 2]) ? in_pindex * 2 + 1 : in_pindex * 2 + 2;
            // Only switches the values if the current parent index is not in its position
            if (hptr->elem[in_pindex] > hptr->elem[in_sindex])
            {
                temp = hptr->elem[in_pindex];
                hptr->elem[in_pindex] = hptr->elem[in_sindex];
                hptr->elem[in_sindex] = temp;
            }
            // Sets the current parent node to the smaller child node;
            in_pindex = in_sindex;
        }
        // Goes to the next parent node and loops.
        pindex = pindex - 1;
    }
}

void heapifyMax(Heap *hptr)
{
    int pindex = (hptr->last - 1) / 2, sindex, temp, in_pindex, in_sindex;
    while (pindex >= 0)
    {
        in_pindex = pindex;
        sindex = (pindex * 2 + 2 > hptr->last || hptr->elem[pindex * 2 + 1] > hptr->elem[pindex * 2 + 2]) ? pindex * 2 + 1 : pindex * 2 + 2;
        in_sindex = sindex;
        while (in_pindex * 2 + 1 <= hptr->last || in_pindex * 2 + 2 <= hptr->last)
        {
            in_sindex = (in_pindex * 2 + 2 > hptr->last || hptr->elem[in_pindex * 2 + 1] > hptr->elem[in_pindex * 2 + 2]) ? in_pindex * 2 + 1 : in_pindex * 2 + 2;
            if (hptr->elem[in_pindex] < hptr->elem[in_sindex])
            {
                temp = hptr->elem[in_pindex];
                hptr->elem[in_pindex] = hptr->elem[in_sindex];
                hptr->elem[in_sindex] = temp;
            }
            in_pindex = in_sindex;
        }
        pindex = pindex - 1;
    }
}

int main()
{
    // Sort array to create Heap with Mininmum as root;
    Heap Hep;
    Hep.elem[0] = 9;
    Hep.elem[1] = 6;
    Hep.elem[2] = 12;
    Hep.elem[3] = 9;
    Hep.elem[4] = 1;
    Hep.elem[5] = 4;
    Hep.elem[6] = 8;
    Hep.elem[7] = 10;
    Hep.last = 7;
    displayHeap(Hep);
    //    heapifyMin(&Hep);
    heapMin(&Hep);
    displayHeap(Hep);
    deleteMin(&Hep);
    displayHeap(Hep);
    heapSortMin(&Hep);
    displayHeap(Hep);
}
