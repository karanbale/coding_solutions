/*
Given an input string s, reverse the order of the words.

A word is defined as a sequence of non-space characters. The words in s will be separated by at least one space.
Return a string of the words in reverse order concatenated by a single space.

Note that s may contain leading or trailing spaces or multiple spaces between two words.
The returned string should only have a single space separating the words. Do not include any extra spaces.


Example 1:
Input: s = "the sky is blue"
Output: "blue is sky the"

Example 2:
Input: s = "  hello world  "
Output: "world hello"
Explanation: Your reversed string should not contain leading or trailing spaces.

Example 3:
Input: s = "a good   example"
Output: "example good a"
Explanation: You need to reduce multiple spaces between two words to a single space in the reversed string.

Example 4:
Input: s = "  Bob    Loves  Alice   "
Output: "Alice Loves Bob"

Example 5:
Input: s = "Alice does not even like bob"
Output: "bob like even not does Alice"

Constraints:

1 <= s.length <= 104
s contains English letters (upper-case and lower-case), digits, and spaces ' '.
There is at least one word in s.
 

Follow-up: If the string data type is mutable in your language, can you solve it in-place with O(1) extra space?
*/

#include "../standardHeaders.h"

void cleanSpaces(char *s) {
    int new1 = 0;
    int old = 0;
    while(s[old] != '\0') {
        // ignore leading white spaces
        while(s[old] != '\0' && s[old] == ' ') {
            old++;
        }
        // if we've already stored with new index, add space
        if(s[old] != '\0' && new1 > 0) {
            s[new1++] = ' ';
        }
        // copy word back into string
        while(s[old] != '\0' && s[old] != ' ') {
            s[new1++] = s[old++];
        }
    }
    s[new1++] = '\0';
}

void reverseWord(char *s, int startIdx, int endIdx) {
    while(startIdx < endIdx) {
        char temp = s[endIdx];
        s[endIdx--] = s[startIdx];
        s[startIdx++] = temp;
    }
}

void helperFunc(char *s) {
    // iterate over s and reverse each word
    int startIdx = 0, endIdx = 0;
    char *temp = s;
    while(*temp != '\0') {
        while(*temp!='\0' && *temp == ' ') {
            ++startIdx; ++temp;
        }
        while(*temp!='\0' && *temp != ' ') {
            ++endIdx; ++temp;
        }
        reverseWord(s, startIdx, endIdx-1);
        startIdx = endIdx;
        ++endIdx;
    }
}

void flip(char *s) {
    int i = 0;
    while(s[i] != '\0') {
        i++;
    }
    reverseWord(s, 0, i-1);
}

char * reverseWords(char *s) {
    // trim spaces from front and end of the string
    cleanSpaces(s);
    // reverse each word in place
    helperFunc(s);
    // reverse entire string
    flip(s);
    return s;
}

