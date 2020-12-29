/*
Given a string s, find the length of the longest substring without repeating characters.

Example 1:
Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.

Example 2:
Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.

Example 3:
Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.

Example 4:
Input: s = ""
Output: 0
 

Constraints:

0 <= s.length <= 5 * 104
s consists of English letters, digits, symbols and spaces.
*/

#include "../standardHeaders.h"

#define max(a,b) ((a) > (b) ? (a) : (b))
#define ASCII_BASIC_SIZE 128
#define ASCII_EXTENDED_SIZE (ASCII_BASIC_SIZE*2)

int lengthOfLongestSubstring(char * s){
    const size_t strLength = strlen(s);
    
    // return for empty string
    if(strLength <1) return 0;

    int hashSet[ASCII_EXTENDED_SIZE] = {0};
    int maxCount = 0, i=0, j=0;

    while(i < strLength && j < strLength){
        if(!hashSet[s[j]]){
            hashSet[s[j++]]=1;
            maxCount = max(maxCount, j-i);
        }
        else{
            hashSet[s[i++]]=0;
        }
    }
    
    return max(maxCount, (j-i));
    
}
