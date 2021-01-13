#include "maxHeap.h"

void insertHeap(heap_t *heap, int data);
int deleteFromHeap(heap_t *heap);
void heapify(heap_t *heap, int idx);
heap_t *createHeap(int heapSize, bool isMinHeap);

int getLeftIndexMaxHeap(int idx){
    return ((2*idx)+1);
}

int getRightIndexMaxHeap(int idx){
    return ((2*idx)+2);
}

int getParentIndex(int idx){
    return ((idx-1)/2);
}

void swap(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

heap_t *createHeap(int heapSize, bool isMinHeap){
    heap_t *heap = malloc(sizeof(heap_t));
    if(!heap) return NULL;
    heap->heapSize = heapSize;
    heap->heapArr = malloc(sizeof(int) * heapSize);
    if(!heap->heapArr) return NULL;
    heap->heapBoundary = 0;
    heap->minHeap = isMinHeap;
    return heap;
}

void heapify(heap_t *heap, int idx){
    // get left child idx
    int leftIdx = getLeftIndexMaxHeap(idx);
    
    // get right child idx
    int rightIdx = getRightIndexMaxHeap(idx);
    
    // Assume current index holds largest value amongst three nodes
    int largestValIdx = idx;

    if(heap->minHeap){
        if(leftIdx < heap->heapBoundary && heap->heapArr[leftIdx] < heap->heapArr[largestValIdx]){
            largestValIdx = leftIdx;
        }
        if(rightIdx < heap->heapBoundary && heap->heapArr[rightIdx] < heap->heapArr[largestValIdx]){
            largestValIdx = rightIdx;
        }
    }
    else{
        if(leftIdx < heap->heapBoundary && heap->heapArr[leftIdx] > heap->heapArr[largestValIdx]){
            largestValIdx = leftIdx;
        }
        if(rightIdx < heap->heapBoundary && heap->heapArr[rightIdx] > heap->heapArr[largestValIdx]){
            largestValIdx = rightIdx;
        }
    }

    // if index of largest value is not same as input index, swap them
    if(largestValIdx != idx){
        swap(&heap->heapArr[idx], &heap->heapArr[largestValIdx]);
        heapify(heap, largestValIdx);
    }

}

// deletes the max item and return
int deleteFromHeap(heap_t *heap){
    if(heap->heapBoundary == 0)
    {
        printf("The heap is empty.\n");
        exit(1);
    }

    int max_item = heap->heapArr[0];

    // replace the first item with the last item
    heap->heapArr[0] = heap->heapArr[heap->heapBoundary-1];
    heap->heapBoundary--;

    // maintain the heap property by heapifying the 
    // first item
    heapify(heap, 0);
    return max_item;
}

void insertHeap(heap_t *heap, int data){
    if(heap->heapBoundary > heap->heapSize){
        printf("Cannot insert item in heap, HEAP IS FULL!\n");
        return;
    }
    // add value to the end of the array
    heap->heapArr[heap->heapBoundary] = data;

    // increment the boundary for next element
    heap->heapBoundary++;

    // get the last index 
    int idx = heap->heapBoundary-1;

    // heapify_bottom_top(heap, heap->heapBoundary);

    if(heap->minHeap){
        // keep swapping current data with its parent, if current data is greater than its parent
        while((idx != 0) && (heap->heapArr[idx] < heap->heapArr[getParentIndex(idx)])){
            swap(&heap->heapArr[getParentIndex(idx)], &heap->heapArr[idx]);
            idx = getParentIndex(idx);
        }
    }
    else{
        // keep swapping current data with its parent, if current data is greater than its parent
        while((idx != 0) && (heap->heapArr[idx] > heap->heapArr[getParentIndex(idx)])){
            swap(&heap->heapArr[getParentIndex(idx)], &heap->heapArr[idx]);
            idx = getParentIndex(idx);
        }
    }
}

void print(heap_t *h){
    int i;
    printf("____________Print Heap_____________\n");
    for(i=0;i< h->heapBoundary;i++){
        printf("-> %d ",h->heapArr[i]);
    }
    printf("->__/\\__\n");
}

int main(){
    int i;
    // heap_t *createHeap(int heapSize, bool isMinHeap)
    heap_t *heap = createHeap(HEAP_SIZE, true); //Min Heap
    if( heap == NULL ){
        printf("__Memory Issue____\n");
        return -1;
    }

    for(i =9;i>0;i--)
        insertHeap(heap, i);

    print(heap);

    for(i=9;i>=0;i--){
        printf(" Pop Minima : %d\n", deleteFromHeap(heap));
        print(heap);
    }
    return 0;
}


