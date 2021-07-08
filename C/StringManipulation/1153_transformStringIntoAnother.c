/*
Given two strings str1 and str2 of the same length,
determine whether you can transform str1 into str2 by doing zero or more conversions.

In one conversion you can convert all occurrences of one character in str1 to any other lowercase English character.
Return true if and only if you can transform str1 into str2.

Example 1:
Input: str1 = "aabcc", str2 = "ccdee"
Output: true
Explanation: Convert 'c' to 'e' then 'b' to 'd' then 'a' to 'c'. Note that the order of conversions matter.

Example 2:
Input: str1 = "leetcode", str2 = "codeleet"
Output: false
Explanation: There is no way to transform str1 to str2.

Constraints:

1 <= str1.length == str2.length <= 104
str1 and str2 contain only lowercase English letters.
*/

#include "../standardHeaders.h"

static inline bool isCharSetFull(char *charSet){
    for(int i=0; i<26; i++){
        if(charSet[i] == 0){
            return false;
        }
    }
    return true;
}

bool canConvert(char * str1, char * str2){
    char char_set[26] = { 0 };
    uint8_t charMap[26] = { 0 };
    
    // if both strings are same, just return, we can transform them
    if(strcmp(str1, str2) == 0) return true;
    
    for (; *str1 != 0; ++str1, ++str2) {
        // printf("*str1: %c\n", *str1);
        if (charMap[*str1-'a'] != 0) {
            // if current character is being transformed into 2 different characters, 
            // that is a failure case
            if (charMap[*str1-'a'] != *str2) return false;
        }
        else{
            // store what is current characters corresponding str2 transformation
            charMap[*str1-'a'] = *str2 ;
            // printf("\tcm[%c]: %c\n",*str1, cm[*str1]);
        }
        // mark this character as seen
        char_set[*str2-'a'] = 1;
    }
    
    // output string has ALL 26 characters present in it
    // we cannot have all 26 characters present in output, we cannot transform our string then
    return !(isCharSetFull(char_set)) ? true : false;
    
}

/*
Sample inputs to test:

"abcdefghijklmnopqrstuvwxyz"
"bcdefghijklmnopqrstuvwxyza"
"abcdefghijklmnopqrstuvwxyz"
"bcadefghijklmnopqrstuvwxzz"
"aabcc"
"ccdee"
"leetcode"
"codeleet"
*/
