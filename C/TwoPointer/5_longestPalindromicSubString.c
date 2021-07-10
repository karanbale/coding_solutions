/*
Given a string s, return the longest palindromic substring in s.

Example 1:
Input: s = "babad"
Output: "bab"
Note: "aba" is also a valid answer.

Example 2:
Input: s = "cbbd"
Output: "bb"

Example 3:
Input: s = "a"
Output: "a"

Example 4:
Input: s = "ac"
Output: "a"

Constraints:

1 <= s.length <= 1000
s consist of only digits and English letters (lower-case and/or upper-case),
*/

#include "../standardHeaders.h"

/**********************************************************************************************/
/******************************** Solution 1 **************************************************/
/**********************************************************************************************/
int expandFromMiddle(char *s, int left, int right);

void printArr(char *s, int size){
    while(*s){
        printf("%c",*s++);
    }
    printf("\n");
}

char * longestPalindromeMethod1(char * s){
    
    if(s == NULL){
        return NULL;
    }

    char *start, *end;
    char *p = s, *subStart = s;
    int maxLen = 1;
    while(*p){
        start = p; end = p;
        
        while(*(end+1) && *(end+1) == *end){
            end++; // skip duplicates
        }
        p = end + 1;
        
        while(*(end + 1) && (start > s) && *(end + 1) == *(start - 1)){
            printf("comparing: %c, %c\n",*(end+1), *(start - 1));
            start--;
            end++;
        }
        if(end - start + 1 > maxLen){
            maxLen = end - start + 1;
            subStart = start;
        }
    }
    
    char *rst = (char *) calloc(maxLen + 1, sizeof(char));
    strncpy(rst, subStart, maxLen);
    return rst;
}

/**********************************************************************************************/
