/*
Given a string s, you can convert it to a palindrome by adding characters in front of it. 
Find and return the shortest palindrome you can find by performing this transformation.

Example 1:
Input: s = "aacecaaa"
Output: "aaacecaaa"

Example 2:
Input: s = "abcd"
Output: "dcbabcd"

Constraints:

0 <= s.length <= 5 * 104
s consists of lowercase English letters only.
*/

#include "../standardHeaders.h"

void reverseString (char *s) {
    char t, *d = s+strlen (s)-1;
    while (d > s) {
        t = *s;
        *s++ = *d;
        *d-- = t;
    }
}

bool checkPalindrome_method1(char * inputString) {
    
    if(strlen(inputString) <= 0){   return false;   }
    int i = 0;
    int j = strlen(inputString)-1;
    while(j > i) {
        if(inputString[i++] != inputString[j--]) {
            return false;
        }
    }
    return true;
}

char * shortestPalindrome(char * s){
    // Algorithm :
    // check if current string is a palindrome
    // if not a palindrome, simply copy one character from end of s and add it to the front of s
    // check if palindrome again
    // if not, add last two characters in reverse order 
    
    if(strlen(s) == 0){
        return s;
    }
    
    // string memory to return 
    char *tempString = malloc(sizeof(char *)*2*strlen(s));
    // reverse copy of input string, helpful for accelerated computations during memcpy
    // if we dont have it, we can copy 1 byte at a time, from end of s, but it will be slow operation
    char *reverseS = malloc(sizeof(char)*strlen(s)+1);
    
    // if malloc failed, return
    if(!tempString || !reverseS){    return 0;   }
    
    // copy string s to tempString, so while loop check does not fail at very first iteration
    strcpy(tempString, s);
    
    // copy string s to reverseS and reverse this string
    strcpy(reverseS, s);
    reverseString(reverseS);
    
    // index to track how many characters are we going to copy from end of s to tempString
    // substract this from strlen(s), to get # of bytes to be copied from end
    // for each incremental cycle, we will copy 1, 2, 3, .... strlen(s)-1 characters until palindrome is found
    int right = strlen(s)-1;
    
    // until string is palindrome, keep running
    while(!checkPalindrome_method1(tempString)){
        // printf("1. %s\n", tempString);
        // empty tempString every iteration, since we need to copy chars to it from index 0
        // we dont want unflushed string
        memset(tempString, 0, strlen(tempString));
        int index = 0;
        int len = strlen(s);
        if(len){
            memcpy(tempString+index, reverseS,(len-right));
        }
        strcpy((tempString+strlen(tempString)), s);
        // printf("\t3. %s\n", tempString);
        right--;
    }
    
    free(reverseS);
    return tempString;
}
