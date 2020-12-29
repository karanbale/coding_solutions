#include "maxHeap.h"

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

void maxHeapify(int *array, int arraySize, int idx){
    // get left child idx
    int leftIdx = getLeftIndexMaxHeap(idx);
    
    // get right child idx
    int rightIdx = getRightIndexMaxHeap(idx);
    
    // Assume current index holds largest value amongst three nodes
    int largestValIdx = idx;
    
    // find if left node holds value > current value
    if((leftIdx < arraySize) && (array[leftIdx] > array[largestValIdx])){
        largestValIdx = leftIdx;
    }
    
    // find if right node holds value > current value
    if((rightIdx < arraySize) && (array[rightIdx] > array[largestValIdx])){
        largestValIdx = rightIdx;
    }
    
    // if index of largest value is not same as input index, swap them
    if(largestValIdx != idx){
        int temp = array[largestValIdx];
        array[idx] = array[largestValIdx];
        array[idx] = temp;
        maxHeapify(array, arraySize, largestValIdx);
    }
    
}

void createMaxHeap(int *array, int arraySize){
    for(int i=arraySize/2; i>0; i--){
        maxHeapify(array, arraySize, i);
    }   
}

// deletes the max item and return
int deleteFromMaxHeap(int *array, int *arraySize){
    if(*arraySize == 0)
    {
        printf("The heap is empty.\n");
        exit(1);
    }
    int max_item = array[0];

    // replace the first item with the last item
    array[0] = array[*arraySize - 1];
    *arraySize = *arraySize - 1;

    // maintain the heap property by heapifying the 
    // first item
    maxHeapify(array, *arraySize, 0);
    return max_item;
}

void insertMaxHeap(int *array, int *arraySize, int data){
    // add value to the end of the array
    array[*arraySize] = data;
    *arraySize += 1;
    // get the last index 
    int idx = *(arraySize-1);

    // keep swapping current data with its parent, if current data is 
    while((idx != 0) && (array[idx] > array[getParentIndex(idx)])){
        swap(&array[getParentIndex(idx)], &array[idx]);
        idx = getParentIndex(idx);
    }
}


