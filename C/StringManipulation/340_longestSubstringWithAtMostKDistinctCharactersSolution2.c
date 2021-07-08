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
    int lenOfDistinctCharacters = 2;
    if(strlen(s) <= lenOfDistinctCharacters) return strlen(s);
    
    int map[ASCII_EXTENDED_SIZE] = {0};
    
    int leftIdxOfInputString = 0;
    int subStrCount = 0, uniqueCharCount = 0;
    // start iterating over string s
    for (int rightIdxOfInputString = 0; rightIdxOfInputString < strlen(s); rightIdxOfInputString++) {
        // update frequence of current character in map table
        map[s[rightIdxOfInputString]]++;
        // keep count of unique characters we're finding, unique since their freq is only 1
        if(map[s[rightIdxOfInputString]] == 1)   uniqueCharCount++;
        // if frequency of unique characters goes beyond k (here k = 2), lets increment our hashSetIdx
        // reduce frequency of each character
        while(uniqueCharCount > lenOfDistinctCharacters){
            map[s[leftIdxOfInputString]]--;
            if(map[s[leftIdxOfInputString]] == 0){
                uniqueCharCount--;
            }
            leftIdxOfInputString++;
        }
        subStrCount = MAX(subStrCount, rightIdxOfInputString - leftIdxOfInputString+1);
        
    }
    return subStrCount;
}

