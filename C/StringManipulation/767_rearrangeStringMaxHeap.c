/*
Given a string S, check if the letters can be rearranged so that two characters that are adjacent to each other are not the same.
If possible, output any possible result.  If not possible, return the empty string.

Example 1:
Input: S = "aab"
Output: "aba"

Example 2:
Input: S = "aaab"
Output: ""

Note:
S will consist of lowercase letters and have length in range [1, 500].
 
*/

#include "../standardHeaders.h"

typedef struct heap{
    int heapSize;
    int heapBoundary;
    int *heapArr;
    bool isMaxHeap;
}heap_t;

void swap(int *x, int *y){
    int temp = *x;
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
    heap_t *heap = (heap_t *)malloc(sizeof(heap_t));
    if(!heap)   return NULL;

    heap->heapArr = malloc(sizeof(int)*heapSize);
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

void printHeap(struct heap *h){
    for (int q = 0; q < 27; q++){
        printf("%d, ", h->heapArr[q]);
    } 
}

char* reorganizeString(char* S){
    int l = strlen(S);
    int s[26]; 
	
	// create max heap
    heap_t *h = createHeap(100, true);

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

    int idx = 0; 

    while(!isHeapEmpty(h)){
        int character1 = -1, character2 = -1, letterCount1 = -1, letterCount2 = -1;
        
        // take first character with max occurance in heap
        int letter = removeHeap(h);
        if(letter != -1){
            letterCount1 = letter / 100;              // get frequence of this character
            // if we have any character whose frequence is more than half the total length, we can never rearrange the string characters to make it unique 
            if (letterCount1 > (l+1)/2) return "";  
            character1 = 'a' + (letter % 100);     // get the character itself
        }

        // take second character with max occurance in heap
        int letter2 = removeHeap(h);
        if(letter2 != -1){
            letterCount2 = letter2 / 100;            // get frequence of this character
            // if we have any character whose frequence is more than half the total length, we can never rearrange the string characters to make it unique 
            if (letterCount2 > (l+1)/2) return "";
            character2 = 'a' + (letter2 % 100);   // get the character itself
        }

        // for first character or for character who is not equal to previous character
        if (idx==0 || character1 != S[idx-1]){
            if(letter != -1){
                S[idx++] = character1;
                letter -= 100;          // reduce freq of the character1 by 1
            }
            if(letter2 != -1){
                S[idx++] = character2;
                letter2 -= 100;          // reduce freq of the character2 by 1
            }
        }
        // if first character is same as previous character, just add second character first and then second character, to achieve uniqueness
        else {
            if(letter2 != -1){
                S[idx++] = character2;
                letter2 -= 100;          // reduce freq of the character2 by 1
            }
            if(letter != -1){
                S[idx++] = character1;
                letter -= 100;          // reduce freq of the character1 by 1
            }
        }
        
        // we're inserting one character at a time, so for characters more than 1 frequency, we need to re-insert them back to the heap, so they can be used next time around
        if (letter >= 100) insertHeap(h, letter); 
        if (letter2 >= 100) insertHeap(h, letter2); 
    }

    return S;
}