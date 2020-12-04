/*
Given two strings s and t , write a function to determine if t is an anagram of s.

Example 1:
Input: s = "anagram", t = "nagaram"
Output: true

Example 2:
Input: s = "rat", t = "car"
Output: false

Note:
You may assume the string contains only lowercase alphabets.

Follow up:
What if the inputs contain unicode characters? How would you adapt your solution to such case?
*/

/*
Sample inputs:

"anagram"
"nagaram"

"aa"
"bb"

*/

#include "../standardHeaders.h"

bool isAnagram(char * s, char * t){
    
    
    if(strlen(s) != strlen(t)){
        return false;
    }
    
    int table[256] = {0};
    
    while(*s){  table[*s++ - 'a']++; }
    while(*t){  table[*t++ - 'a']--; }
    
    for(int i=0; i<256; i++){
        if(table[i] != 0){
            return false;
        }
    }
    return true;
}
