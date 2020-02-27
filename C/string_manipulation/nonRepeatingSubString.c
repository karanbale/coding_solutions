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

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <stdarg.h>

#define ENABLE_PRINTS 
#define max(a,b) ((a) > (b) ? (a) : (b))

void printf_wrapper(const char * message, ...) {
    va_list args;
    va_start(args, message);
#ifdef ENABLE_PRINTS
    vprintf(message, args);
#endif
    va_end(args);
}

// int lengthOfLongestSubstring(char * s){
    
//     int maxStrLength = 0, subIndex=0, subStrLength=0, maxRetLength=0;
//     size_t strLength = strlen(s);
//     bool charRepeated = false, firstSubStrFound=false;
    
//     // return for empty string
//     if(strLength <1) return maxStrLength;
    
//     // return for overflow
//     if(strLength > INT32_MAX) return maxStrLength;

//     char subStr[strLength];

//     while(*s != '\0'){
//         printf_wrapper("char: %c\t", *s);
//         // compare elements from 
//         for(subIndex = 0 ; subIndex < subStrLength; subIndex++){
//             if(subStr[subIndex] == *s){
//                 firstSubStrFound = true;
//                 break;
//             }
//         }
//         if(firstSubStrFound){
//             maxRetLength = max(maxRetLength, subStrLength);
//             subStrLength = 0;
//             firstSubStrFound = false;
//             printf_wrapper("subStr: %s \n", subStr);
//         }
//         subStr[subStrLength++] = *s;
//         s++;
//     }
    
//     return max(maxRetLength, subStrLength);
// }


int lengthOfLongestSubstring(char * s){
    
    int maxStrLength = 0, subIndex=0, subStrEnd=0, subStrStart=0, maxRetLength=0, subStrLength=0;
    int count=0;
    size_t strLength = strlen(s);
    bool charRepeated = false, firstSubStrFound=false;
    
    // return for empty string
    if(strLength <1) return maxStrLength;
    
    // return for overflow
    if(strLength > INT32_MAX) return maxStrLength;

    char subStr[strLength];

    while(*s != '\0'){
        printf_wrapper("char: %c\t", *s);
        subStr[subStrEnd] = *s;
        // compare elements from subString with all its predecessors 
        for(subIndex = subStrStart; subIndex < subStrEnd; subIndex++){
            if((subStr[subIndex] == *s) && (count != subIndex)){
                printf_wrapper("found %c %c\n",subStr[subIndex],*s);
                subStrStart = subIndex+1;
                firstSubStrFound = true;
                break;
            }
        }
        if(firstSubStrFound){
            maxRetLength = max(maxRetLength, (subStrEnd-subStrStart));
            // subStrEnd = 0;
            firstSubStrFound = false;
            printf_wrapper("subStrEnd: %d\t", subStrEnd);
            printf_wrapper("subStrS: %s \t", subStr);
            printf_wrapper("subStrStart: %d\t", subStrStart);
            printf_wrapper("subStrC: %c \n", subStr[subStrStart]);
        }
        subStrEnd++;
        count++;
        s++;
    }
    printf_wrapper("subStrS: %s \n", subStr);
    printf_wrapper("\n");

    return max(maxRetLength, subStrEnd);
    
}


int main(void){

    // printf("longest subStrLength: %d\n", lengthOfLongestSubstring("pwwkew"));
    // printf("longest subStrLength: %d\n", lengthOfLongestSubstring("abbabcabcabbcc"));
    // printf("longest subStrLength: %d\n", lengthOfLongestSubstring("bbbbbbb"));
    // printf("longest subStrLength: %d\n", lengthOfLongestSubstring("abcdeabc"));
    // printf("longest subStrLength: %d\n", lengthOfLongestSubstring(""));
    // printf("longest subStrLength: %d\n", lengthOfLongestSubstring(" "));
    // printf("longest subStrLength: %d\n", lengthOfLongestSubstring("b"));
    printf("longest subStrLength: %d\n", lengthOfLongestSubstring("dvdf"));

    return 0;

}
