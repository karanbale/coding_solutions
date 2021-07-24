/**
 * Given a string, find the length of the longest substring T that contains at most k distinct characters.
 * Example 1:
 *      Input: s = "eceba", k = 2
 *      Output: 3
 *      Explanation: T is "ece" which its length is 3.
 * 
 * Example 2:
 *      Input: s = "aa", k = 1
 *      Output: 2
 *      Explanation: T is "aa" which its length is 2.
*/

#include "../standardHeaders.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define BASIC_ASCII 128
#define EXTENDED_ASCII (BASIC_ASCII*2)

typedef struct{
    int hashSet[EXTENDED_ASCII];
    int uniqueCharCount;
} hash;

void insertHash(hash *h, char c) {
    // character never seen before
    if(h->hashSet[c] == 0) {
        h->uniqueCharCount++;
    }
    h->hashSet[c]++;
}

void removeHash(hash *h, char c) {
    if(h->hashSet[c]) {
        h->hashSet[c]--;
        if(h->hashSet[c] == 0) h->uniqueCharCount--;
    }
}

int getHashSetUniqueCharCount(hash *h) {
    return h->uniqueCharCount;
}

int lengthOfLongestSubstringKDistinct(char * s, int k){
    hash h;
    h.uniqueCharCount = 0;
    memset(h.hashSet, 0, (sizeof(int)*EXTENDED_ASCII));

    int startIdx = 0, currIdx = 0, maxCount = 0;
    // start iterating over string s
    while(s[currIdx]) {
        // keep tracking length
        // insert character to hashSet
        insertHash(&h, s[currIdx++]);
        // if the character count in hash-map exceeds k, start removing characters from left index
        while(getHashSetUniqueCharCount(&h) > k) {
            // if more, pop items from hashSet, update max length
            removeHash(&h, s[startIdx++]);
        }
        // get the max count between max seen so far and current length - first valid kth element
        maxCount = MAXß(maxCount, currIdx - startIdx);
    }
    return maxCount;
}
