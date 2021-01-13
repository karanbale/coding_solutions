#include "../../standardHeaders.h"

#define HEAP_SIZE 20

typedef struct heap{
    int *heapArr;
    int heapSize;
    int heapBoundary;
    bool minHeap;
}heap_t;

void swap(int *x, int *y);
int getLeftIndexMaxHeap(int idx);
int getRightIndexMaxHeap(int idx);
int getParentIndex(int idx);
int deleteFromMaxHeap(int *array, int *arraySize);
void maxHeapify(int *array, int arraySize, int idx);
void createMaxHeap(int *array, int arraySize);
void insertMaxHeap(int *array, int *arraySize, int data);
