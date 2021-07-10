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




/**********************************************************************************************/
/******************************** Solution 2 **************************************************/
/**********************************************************************************************/
char * longestPalindromeMethod2(char * s){
    if(s == NULL){
        return NULL;
    }

    int maxLen = 0;
    int start = 0;
    int end = 0;

    for(int i=0; i<strlen(s); i++){
        // handle the case, where middle word of palindrome has no matching word. e.g. 'e' in "racecar"
        int len1 = expandFromMiddle(s, i, i);
        // handle the case, where we have a symmetric palindrome. e.g. "aabbaa", this palindrome has all characters
        // repeating themselves around center (NOTE: center is not a character here)
        int len2 = expandFromMiddle(s, i, i+1);
        maxLen = fmax(len1, len2);

        // if current palindrome's length is bigger than existing indexes of substring, update it.
        // i is the center of the palindrome, so start would be to the left of ith index, by maxLen/2 (since i is in the middle)
        // i is the center of the palindrome, so end would be to the right of ith index, by maxLen/2 (since i is in the middle)
        if(maxLen > end - start){
            start = i-((maxLen-1)/2);
            end = i+(maxLen/2);
        }
    }

    char *rst = (char *) calloc((end+1-start) + 1, sizeof(char));
    strncpy(rst, (s+start), (end+1-start));
    return rst;

}

int expandFromMiddle(char *s, int left, int right){
    if((s == NULL) || (left > right)){
        return 0;
    }

    // ensure, our left and right indices are within legal bounds
    // check if left and right characters are same, to achieve palindrome
    while((left >= 0) && (right < strlen(s)) && (s[left] == s[right])){
        left--;
        right++;
    }

    // return length of palindrome, substract 1 to maintain legal bounds of index, since index start at 0
    return right - left - 1; 
}

/**********************************************************************************************/