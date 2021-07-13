#include "heap.h"
#include "queue.h"

int getParentIdx(int idx) {
    return ((idx-1)/2);
}

int getLeftChildIdx(int idx) {
    return ((idx*2)+1);
}

int getRightChildIdx(int idx) {
    return ((idx*2)+2);
}

heap_t *createHeap(int heapSize, bool isMaxHeap) {
    heap_t *heap = (heap_t *) malloc(sizeof(heap_t));
    if(!heap)   return NULL;
    
    heap->heapArr = (size_t *) malloc(sizeof(size_t)*heapSize);
    if(!heap->heapArr) return NULL;
    
    heap->heapSize = heapSize;
    heap->heapBoundary = 0;
    heap->isMaxHeap = isMaxHeap;

    return heap;
}

bool isHeapEmpty(heap_t *heap) {
    return heap->heapBoundary == 0;
}

bool isHeapFull(heap_t *heap) {
    return heap->heapBoundary == heap->heapSize;
}

void insertHeap(heap_t *heap, int data) {
    if(isHeapFull(heap)){
        printf("Heap is FULL\n");
        return;
    }
    heap->heapArr[heap->heapBoundary] = data;
    int index = heap->heapBoundary;
    heap->heapBoundary++;
    
    if(heap->isMaxHeap){
        while(index != 0 && heap->heapArr[index] > heap->heapArr[getParentIdx(index)]){
            swap(&heap->heapArr[index], &heap->heapArr[getParentIdx(index)]);
            index = getParentIdx(index);
        }
    }
    else{
        while(index != 0 && heap->heapArr[index] < heap->heapArr[getParentIdx(index)]){
            swap(&heap->heapArr[index], &heap->heapArr[getParentIdx(index)]);
            index = getParentIdx(index);
        }
    }
}

void heapify(heap_t *heap, int idx) {
    
    int leftIdx = getLeftChildIdx(idx);
    int rightIdx = getRightChildIdx(idx);
    int parentIdx = getParentIdx(idx);
    
    int largestValIdx = idx;
    
    if(heap->isMaxHeap){
        if(leftIdx < heap->heapBoundary && heap->heapArr[leftIdx] > heap->heapArr[largestValIdx]) {
            largestValIdx = leftIdx;
        }
        if(rightIdx < heap->heapBoundary && heap->heapArr[rightIdx] > heap->heapArr[largestValIdx]) {
            largestValIdx = rightIdx;
        }
    }
    else {
        if(leftIdx < heap->heapBoundary && heap->heapArr[leftIdx] < heap->heapArr[largestValIdx]) {
            largestValIdx = leftIdx;
        }
        if(rightIdx < heap->heapBoundary && heap->heapArr[rightIdx] < heap->heapArr[largestValIdx]){
            largestValIdx = rightIdx;
        }
    }
    
    if(largestValIdx != idx) {
        swap(&heap->heapArr[largestValIdx], &heap->heapArr[idx]);
        heapify(heap, largestValIdx);
    }
}

int peekHeap(heap_t *heap) {
    return heap->heapArr[0];
}

int removeHeap(heap_t *heap) {
    if(isHeapEmpty(heap))  return -1;
    
    int retVal = heap->heapArr[0];
    heap->heapArr[0] = heap->heapArr[heap->heapBoundary-1];
    heap->heapBoundary--;
    heapify(heap, 0);
    
    return retVal;
}

void destroyHeap(heap_t *heap) {
    free(heap);
}

void printHeap(struct heap *h) {
    for (int q = 0; q < 27; q++) {
        if(h->heapArr[q]>0){
            printf("%ld, ", h->heapArr[q]);
        }
    }
}
