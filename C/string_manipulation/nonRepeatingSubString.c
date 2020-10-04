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
    
    int maxStrLength = 0, subIndex=0, subStrEnd=0, subStrStart=0, maxRetLength=0;
    int count=0;
    const size_t strLength = strlen(s);    
    
    // return for empty string
    if(strLength <1) return maxStrLength;
    
    // return for overflow
    if(strLength > INT32_MAX) return maxStrLength;

    char subStr[strLength];

    while(*s != '\0'){
        // printf_wrapper("char: %c\t", *s);
        subStr[subStrEnd] = *s;
        // compare elements from subString with all its predecessors 
        for(subIndex = subStrStart; subIndex < subStrEnd; subIndex++){
            if((subStr[subIndex] == *s) && (count != subIndex)){                
                maxRetLength = max(maxRetLength, (subStrEnd-subStrStart));
                subStrStart = subIndex+1;                
                break;
            }
        }
        subStrEnd++;
        count++;
        s++;
    }

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
