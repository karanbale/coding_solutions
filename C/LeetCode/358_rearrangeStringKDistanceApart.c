/*
Given a non-empty string s and an integer k, rearrange the string such that the same characters are at least distance k from each other.
All input strings are given in lowercase letters. If it is not possible to rearrange the string, return an empty string "".

Example 1:
Input: s = "aabbcc", k = 3
Output: "abcabc" 
Explanation: The same letters are at least distance 3 from each other.

Example 2:
Input: s = "aaabc", k = 3
Output: "" 
Explanation: It is not possible to rearrange the string.

Example 3:
Input: s = "aaadbbcc", k = 2
Output: "abacabcd"
Explanation: The same letters are at least distance 2 from each other.
*/

#include "../standardHeaders.h"

typedef struct queue{
    int *queueArr;
    int queueSize;
    int front;
    int rear;
    int queueItemCount;
}queue_t;

bool isQueueEmpty(queue_t *queue){
    return queue->queueItemCount == 0;
}

bool isQueueFull(queue_t *queue){
    return queue->queueItemCount == queue->queueSize;
}

queue_t *createQueue(int queueSize){
    queue_t *queue = (queue_t *) malloc(sizeof(queue_t));
    if(!queue)    return NULL;
    queue->queueArr = (int *) malloc(sizeof(int)*queueSize);
    if(!queue->queueArr)    return NULL;
    queue->front = 0;
    queue->queueItemCount = 0;
    queue->rear = -1;
    queue->queueSize = queueSize;
    return queue;
}

void queueEnqueue(queue_t *queue, int data){
    if(isQueueFull(queue)) return;
    queue->queueArr[++queue->rear] = data;
    queue->queueItemCount++;
}

int queueDequeue(queue_t *queue){
    if(isQueueEmpty(queue))    return 0;
    queue->queueItemCount--;
    return queue->queueArr[queue->front++];
}

void destroyQueue(queue_t *queue){
    free(queue->queueArr);
    free(queue);
}

typedef struct heapStruct{
    size_t freqCount;
    size_t nextIndex;
}heapStruct_t;

typedef struct heap{
    size_t heapSize;
    size_t heapBoundary;
    size_t *heapArr;
    bool isMaxHeap;
}heap_t;

void swap(size_t *x, size_t *y){
    size_t temp = *x;
    *x = *y;
    *y = temp;
}

int getParentIdx(int idx){
    return ((idx-1)/2);
}

int getLeftChildIdx(int idx){
    return ((idx*2)+1);
}

int getRightChildIdx(int idx){
    return ((idx*2)+2);
}

heap_t *createHeap(int heapSize, bool isMaxHeap){
    heap_t *heap = (heap_t *) malloc(sizeof(heap_t));
    if(!heap)   return NULL;
    
    heap->heapArr = (size_t *) malloc(sizeof(int)*heapSize);
    if(!heap->heapArr) return NULL;
    
    heap->heapSize = heapSize;
    heap->heapBoundary = 0;
    heap->isMaxHeap = isMaxHeap;

    return heap;
}

bool isHeapEmpty(heap_t *heap){
    return heap->heapBoundary == 0;
}

bool isHeapFull(heap_t *heap){
    return heap->heapBoundary == heap->heapSize;
}

void insertHeap(heap_t *heap, int data){
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

void heapify(heap_t *heap, int idx){
    
    int leftIdx = getLeftChildIdx(idx);
    int rightIdx = getRightChildIdx(idx);
    int parentIdx = getParentIdx(idx);
    
    int largestValIdx = idx;
    
    if(heap->isMaxHeap){
        if(leftIdx < heap->heapBoundary && heap->heapArr[leftIdx] > heap->heapArr[largestValIdx]){
            largestValIdx = leftIdx;
        }
        if(rightIdx < heap->heapBoundary && heap->heapArr[rightIdx] > heap->heapArr[largestValIdx]){
            largestValIdx = rightIdx;
        }
    }
    else{
        if(leftIdx < heap->heapBoundary && heap->heapArr[leftIdx] < heap->heapArr[largestValIdx]){
            largestValIdx = leftIdx;
        }
        if(rightIdx < heap->heapBoundary && heap->heapArr[rightIdx] < heap->heapArr[largestValIdx]){
            largestValIdx = rightIdx;
        }
    }
    
    if(largestValIdx != idx){
        swap(&heap->heapArr[largestValIdx], &heap->heapArr[idx]);
        heapify(heap, largestValIdx);
    }
}

int removeHeap(heap_t *heap){
    if(isHeapEmpty(heap))  return -1;
    
    int retVal = heap->heapArr[0];
    heap->heapArr[0] = heap->heapArr[heap->heapBoundary-1];
    heap->heapBoundary--;
    heapify(heap, 0);
    
    return retVal;
}

void destroyHeap(heap_t *heap){
    free(heap);
}

void printHeap(struct heap *h){
    for (int q = 0; q < 27; q++){
        if(h->heapArr[q]>0){
            printf("%ld, ", h->heapArr[q]);
        }
    } 
}

char * rearrangeString(char * S, int K){
    if(K<2) return S;
    
    int l = strlen(S);
    int s[26]; 
	
	// create max heap
    heap_t *h = createHeap(140000, true);
    queue_t *waitQueue = createQueue(140000);

    // initialize the entire array to 0
    memset(s, 0, sizeof(int) * 26);
    
    // store occurance frequency of each character 
    // for each frequency just add 100
    // e.g. if a character occurs 3 times, its frequency is 300
    for (int n = 0; n < l; n++) s[S[n]-97] += 100;   

    // for each character add its index value to the frequency
    // this will be later used to add to 0x61, to retrieve actual letter value of this index
    // e.g. s[1] = 101 => (101%100)+0x61 = 1 + 0x61 = 0x62 = 'b'
    for (int i = 0; i < 26; ++i) s[i] += i;
    
    // for every character found in given string, start adding it to the max heap
    for (int i = 0; i < 26; ++i) {
        if (s[i] >= 100) insertHeap(h, s[i]);       
    }
    
    // printHeap(h);
    
    int idx = 0; 
    // printf("K:%d, S:%s\n",K, S);
    while(!isHeapEmpty(h)){
        int character1 = -1;
        // take first character with max occurance in heap
        int letter = removeHeap(h);
        // if character is valid
        if(letter != -1){
            character1 = 'a' + (letter % 100);      // get the character itself
            letter -= 100;                          // reduce freq of the letter by 1
            
            // add the character to the string
            S[idx++] = character1;
            
            // add this character to the wait queue until its turn which will be after adding K characters
            queueEnqueue(waitQueue, letter);
            // if added K unique characters to the wait queue, pop character from wait queue and add it back to your heap, to be used next
            if(waitQueue->queueItemCount >= K){
                int item = queueDequeue(waitQueue);
                if(item >= 100) insertHeap(h, item);    // make sure character you've popped has valid frequence
            }
        }
    }

    destroyQueue(waitQueue);
    destroyHeap(h);
    
    // if you've added all the characters from input string then your idx must be equal to length of input string
    return (idx < l) ? "" : S;
}
