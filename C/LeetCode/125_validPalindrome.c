/*
Given a string s, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.

Example 1:
Input: s = "A man, a plan, a canal: Panama"
Output: true
Explanation: "amanaplanacanalpanama" is a palindrome.

Example 2:
Input: s = "race a car"
Output: false
Explanation: "raceacar" is not a palindrome.

Constraints:

1 <= s.length <= 2 * 105
s consists only of printable ASCII characters.
*/

#include "../standardHeaders.h"

/*
Strip the string off of all characters except alphanumeric characters
run isPalindrome function on it
odd length palindrome is a palindrome around 1 char at its center
even length palindrome is a palindrome around 2 char at its center or no center at all.

instead of stripping, just add checks where we ignore all non-alphanumeric characters

"amanaplanacanalpanama"
check if its odd length palindrome or even length palindrome (check for both maybe?)

sLen = strlen(s)
leftIdx = 0, rightIdx=strlen(s)-1
while(leftIdx < rightIdx) {
    if(s[leftIdx++] != s[rightIdx--]) {
    return false;
    }
}
return true;

while((leftIdx<sLen) && (rightIdx>= 0) && (s[leftIdx] == s[rightIdx]))

*/

bool isPalindrome(char * s){
    int sLen = strlen(s);
    if(sLen == 0) return false;
    char *newStr = (char *)calloc(sizeof(char), sLen+1);
    char *tempStr = s;
    int idx = 0;
    while(*tempStr) {
        if(isalnum(*tempStr)) newStr[idx++] = *tempStr;
        tempStr++;
    }
    newStr[idx] = '\0';
    int leftIdx = 0, rightIdx = idx-1;
    for(; (leftIdx<rightIdx) && (tolower(newStr[leftIdx]) == tolower(newStr[rightIdx])); leftIdx++, rightIdx--) {
        0;
    }
    free(newStr);
    return (leftIdx<rightIdx) ? false : true;
}

