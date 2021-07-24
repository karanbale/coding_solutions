/*
Given a string s, return true if the s can be palindrome after deleting at most one character from it.

Example 1:
Input: s = "aba"
Output: true

Example 2:
Input: s = "abca"
Output: true
Explanation: You could delete the character 'c'.

Example 3:
Input: s = "abc"
Output: false
 

Constraints:

1 <= s.length <= 105
s consists of lowercase English letters.
*/

#include "../standardHeaders.h"

bool validPalindrome(char * s){
    int sLen = strlen(s);
    int leftIdx = 0, rightIdx = sLen-1, maxPermissibleFaultyChars = 1;
    for(; (leftIdx < rightIdx); leftIdx++, rightIdx--) {
        if(s[leftIdx] != s[rightIdx]) {
            int leftIdx1 = leftIdx, rightIdx1 = rightIdx-1;
            while((leftIdx1 < rightIdx1) && (s[leftIdx1] == s[rightIdx1])) { leftIdx1++; rightIdx1--;}
            int leftIdx2 = leftIdx+1, rightIdx2 = rightIdx;
            while((leftIdx2 < rightIdx2) && (s[leftIdx2] == s[rightIdx2])) { leftIdx2++; rightIdx2--;}
            return leftIdx1 >= rightIdx1 || leftIdx2 >= rightIdx2;
        }
    }
    return true;
}

