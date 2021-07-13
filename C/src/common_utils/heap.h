#include "common.h"

typedef struct heap {
    size_t heapSize;
    size_t heapBoundary;
    size_t *heapArr;
    bool isMaxHeap;
}heap_t;

heap_t *createHeap(int heapSize, bool isMaxHeap);
bool isHeapEmpty(heap_t *heap);
bool isHeapFull(heap_t *heap);
int peekHeap(heap_t *heap);
void insertHeap(heap_t *heap, int data);
void heapify(heap_t *heap, int idx);
int removeHeap(heap_t *heap);
void destroyHeap(heap_t *heap);

