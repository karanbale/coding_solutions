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

#include "MaxHeap_Header.h"
#include "common.h"
#include "queue.h"
#include "heap.h"

char * rearrangeStringKDistanceApart(char * S, int K) {
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
    while(!isHeapEmpty(h)) {
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
