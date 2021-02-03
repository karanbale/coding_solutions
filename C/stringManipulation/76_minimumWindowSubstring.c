/*
Given two strings s and t, return the minimum window in s which will contain all the characters in t.
If there is no such window in s that covers all characters in t, return the empty string "".

Note that If there is such a window, it is guaranteed that there will always be only one unique minimum window in s.

Example 1:

Input: s = "ADOBECODEBANC", t = "ABC"
Output: "BANC"
Example 2:

Input: s = "a", t = "a"
Output: "a"
 
Constraints:

1 <= s.length, t.length <= 105
s and t consist of English letters.
 

Follow up: Could you find an algorithm that runs in O(n) time?
*/

#include "../standardHeaders.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define ASCII_BASIC_SIZE 128
#define ASCII_EXTENDED_SIZE (ASCII_BASIC_SIZE*2)

typedef struct Set {
    // int *countArr;
    int countArr[ASCII_EXTENDED_SIZE];
    size_t size;
    size_t numOfItems;
    
}set_t;

inline static set_t *createHashSet(size_t size){
    set_t *hashSet = (set_t *) malloc(sizeof(set_t));
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

inline static int set_count(set_t *set, char c)
{
    return set->countArr[(int)c];
}

void set_remove(set_t *set, char c)
{
    // reduce freq of char c
    if(set->countArr[(int)(c)] > 0){
        set->countArr[(int)(c)]--;
        // if freq of this character is 0, we've no more c characters left in our string
        // hence reduce the num of items 
        if(set_count(set, c) == 0){
            set->numOfItems--;
        }
    }
}

char * minWindow(char * s, char * t){
    int lenOfS = strlen(s);
    int lenOfT = strlen(t);
    if(lenOfT > lenOfS) return "";
        
    // create dummy hash-map 
    set_t *hashSetT = createHashSet(strlen(t));
    memset(hashSetT->countArr,0,ASCII_EXTENDED_SIZE*sizeof(int));
    
    set_t *hashSetS = createHashSet(strlen(t));
    memset(hashSetS->countArr,0,ASCII_EXTENDED_SIZE*sizeof(int));

    for (int i = 0; i < strlen(t); i++) {
        set_add(hashSetT, t[i]);
    }

    int leftIdx = 0;
    int subStrCount = INT32_MAX;
    int charCount = 0;
    int subStrStartIdx = 0;
    
    // start iterating over string s
    for (int rightIdx = 0; rightIdx < lenOfS; rightIdx++) {
        // check if current char in S, exists in T,
        // it it exists, reduce its freq count
        // keep a count of how many unique characters in S exist in T
        // if char exists in T
        if(set_count(hashSetT, s[rightIdx]) > 0){
            // add char to S hashSet
            set_add(hashSetS, s[rightIdx]);
            // if count of char in T is greater than equal to char count in S
            if(set_count(hashSetS, s[rightIdx]) <= set_count(hashSetT, s[rightIdx])){
                // printf("%c : %d, ",s[rightIdx],rightIdx);
                charCount++;
            }
        }

        // as soon as this count goes beyond size of T, lets try to squeeze window
        // from left and minimize our
        if(charCount == lenOfT) {
            // printf("rightIdx: %d, leftIdx: %d, subStrCount: %d\n",rightIdx, leftIdx, subStrCount);
            // start squeezing the window from left
            // remove any character that does not exist in T or its freq of occurance in S > freq of occurance in T
            while((set_count(hashSetS, s[leftIdx]) > set_count(hashSetT, s[leftIdx])) ||
                    (set_count(hashSetT, s[leftIdx]) == 0)){
                set_remove(hashSetS, s[leftIdx]);
                leftIdx++;
            }
            // if current substr is smaller than previous substr, lets consider it
            if(subStrCount > (rightIdx-leftIdx+1)){
                subStrCount = rightIdx-leftIdx+1;
                subStrStartIdx = leftIdx;
            }
        }
    }
    
    char *result = NULL;
    if(subStrCount != INT32_MAX)
    {
        result = (char*) malloc((subStrCount+1)*sizeof(char));
        strncpy(result, s+subStrStartIdx, subStrCount);
        result[subStrCount] = '\0';
    }
    else
    {
        result = (char*) malloc(1*sizeof(char));
        result[0] = '\0';
    }
    free(hashSetS);
    free(hashSetT);
    
    return result;
}

/*
Inputs to test:
"aa"
"bb"
"aa"
"aa"
"ADOBECODEBANC"
"ABC"
"a"
"a"
"abc"
"cba"
*/