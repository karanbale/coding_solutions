/*

Given an integer array nums and an integer k, return the kth largest element in the array.
Note that it is the kth largest element in the sorted order, not the kth distinct element.

Example 1:

Input: nums = [3,2,1,5,6,4], k = 2
Output: 5
Example 2:

Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
Output: 4

Constraints:

1 <= k <= nums.length <= 104
-104 <= nums[i] <= 104

*/

#include "../standardHeaders.h"

typedef struct heap {
    ssize_t heapSize;
    ssize_t heapBoundary;
    ssize_t *heapArr;
    bool isMaxHeap;
}heap_t;

void swap(ssize_t *idx1, ssize_t *idx2) {
    ssize_t temp = *idx1;
    *idx1 = *idx2;
    *idx2 = temp;
}

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
    
    heap->heapArr = (ssize_t *) malloc(sizeof(ssize_t)*heapSize);
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
    free(heap->heapArr);
    free(heap);
}

int findKthLargest(int* nums, int numsSize, int k){
    // create max heap
    heap_t *h = createHeap(numsSize*2, true);
    // for every character found in given string, start adding it to the max heap
    for (int i = 0; i < numsSize; ++i) {
        insertHeap(h, nums[i]);       
    }
    int kthElement;
    while(k) {
        kthElement = removeHeap(h);
        k--;
    }
    destroyHeap(h);
    return kthElement;
}