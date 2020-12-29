#include "../../standardHeaders.h"

void swap(int *x, int *y);
int getLeftIndexMaxHeap(int idx);
int getRightIndexMaxHeap(int idx);
int getParentIndex(int idx);
int deleteFromMaxHeap(int *array, int *arraySize);
void maxHeapify(int *array, int arraySize, int idx);
void createMaxHeap(int *array, int arraySize);
void insertMaxHeap(int *array, int *arraySize, int data);
