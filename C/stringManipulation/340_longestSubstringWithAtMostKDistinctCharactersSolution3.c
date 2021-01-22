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
#define ASCII_BASIC_SIZE 128
#define ASCII_EXTENDED_SIZE (ASCII_BASIC_SIZE*2)

typedef struct Set {
    // int *countArr;
    int countArr[ASCII_EXTENDED_SIZE];
    size_t size;
    size_t numOfItems;
    
}set_t;

set_t *createHashSet(size_t size){
    set_t *hashSet = malloc(sizeof(set_t));
    hashSet->size = size;
    hashSet->numOfItems = 0;
    return hashSet;
}

void set_add(set_t *set, char c)
{
    if(set->countArr[(int)c] == 0){
        set->numOfItems++;
    }
    set->countArr[(int)c]++;
}

void set_remove(set_t *set, char c)
{
    // reduce freq of char c
    set->countArr[(int)(c)]--;

    // if freq of this character is 0, we've no more c characters left in our string
    // hence reduce the num of items 
    if(set->countArr[(int)(c)] == 0){
        set->numOfItems--;
    }
}

int lengthOfLongestSubstringTwoDistinct(char * s){
    
    if(strlen(s) <= 2) return strlen(s);

    // create dummy hash-map 
    set_t *hashSet = createHashSet(strlen(s));
    memset(hashSet->countArr,0,ASCII_EXTENDED_SIZE*sizeof(int));
    
    int hashSetIdx = 0;
    int subStrCount = 0;

    // start iterating over string s
    for (int i = 0; i < strlen(s); i++) {
        set_add(hashSet, s[i]);
        
        while ((hashSet->numOfItems) > 2) {
            set_remove(hashSet, s[hashSetIdx++]);
        }
        
        subStrCount = MAX(subStrCount, i - hashSetIdx + 1);
    }
    
    free(hashSet);
    return subStrCount;
}


