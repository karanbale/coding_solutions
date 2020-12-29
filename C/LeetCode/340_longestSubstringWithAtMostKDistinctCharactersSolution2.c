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

int lengthOfLongestSubstringTwoDistinct(char * s){
    
    if(strlen(s) <= 2) return strlen(s);
    
    int map[ASCII_EXTENDED_SIZE] = {0};
    
    int hashSetIdx = 0, inputStrIdx = 0;
    int subStrCount = 0, count = 0;
    // start iterating over string s
    for (int i = 0; i < strlen(s); i++) {
        map[s[i]]++;
        if(map[s[i]] == 1)   count++;
        
        while(count > 2){
            map[s[hashSetIdx]]--;
            if(map[s[hashSetIdx]] == 0){
                count --;
            }
            hashSetIdx++;
        }
        subStrCount = MAX(subStrCount, i - hashSetIdx+1);
        
    }
    return subStrCount;
}

