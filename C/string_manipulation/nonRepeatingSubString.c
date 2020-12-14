/*
Given a string, find the length of the longest substring without repeating characters.

Example 1:

Input: "abcabcbb"
Output: 3 
Explanation: The answer is "abc", with the length of 3. 
Example 2:

Input: "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.
Example 3:

Input: "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3. 
             Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
*/

#include "string_manipulation_headers.h"

int lengthOfLongestSubstring(const char * s);

#define max(a,b) ((a) > (b) ? (a) : (b))

int lengthOfLongestSubstring(const char * s){
    
    int maxStrLength = 0, subStrEnd=0, subStrStart=0, maxRetLength=0;
    const size_t strLength = strlen(s);    
    
    // return for empty string
    if(strLength <1) return maxStrLength;
    
    // return for overflow
    if(strLength > INT32_MAX) return maxStrLength;

    // an array to store all characters pop'd from s 
    char subStr[strLength];

    // iterate over string s
    while(*s != '\0'){
        // keep adding new char to the end of array
        subStr[subStrEnd] = *s;
        
        // compare elements from subString with all its predecessors 
        for(int i = subStrStart; i < subStrEnd; i++){
            // if current character in substring with curr input string character
            // curr input string char is not yet in substring
            // so if there is a match, then we know its a duplicate
            if(subStr[i] == *s){
                // find longest non-repeating string length
                maxRetLength = max(maxRetLength, (subStrEnd-subStrStart));
                subStrStart = i+1;                
                break;
            }
        }
        subStrEnd++;
        s++;
    }

    // we may run into a possiblitiy where we reach the end of input string while
    // traversing, and we never found a duplicate character
    // consider this possibility while returning your answer
    return max(maxRetLength, (subStrEnd-subStrStart));
    
}

int main(void){

    printf("longest subStrLength: %d\n\n", lengthOfLongestSubstring("pwwkew"));
    printf("longest subStrLength: %d\n\n", lengthOfLongestSubstring("abbabcabcabbcc"));
    printf("longest subStrLength: %d\n\n", lengthOfLongestSubstring("bbbbbbb"));
    printf("longest subStrLength: %d\n\n", lengthOfLongestSubstring("abcabcbb"));
    printf("longest subStrLength: %d\n\n", lengthOfLongestSubstring(""));
    printf("longest subStrLength: %d\n\n", lengthOfLongestSubstring(" "));
    printf("longest subStrLength: %d\n\n", lengthOfLongestSubstring("b"));
    printf("longest subStrLength: %d\n\n", lengthOfLongestSubstring("dvdf"));

    return 0;

}
