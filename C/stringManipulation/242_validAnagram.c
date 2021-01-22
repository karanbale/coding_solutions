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

#define ASCII_BASIC_SIZE 128
#define ASCII_EXTENDED_SIZE (ASCII_BASIC_SIZE*2)

bool isAnagram(char * s, char * t){
    
    int hashSet[ASCII_EXTENDED_SIZE] = {0};
    
    while(*s){  hashSet[(int)*s++]++;    }
    while(*t){  hashSet[(int)*t++]--;    }
    
    for(int i=0; i<ASCII_EXTENDED_SIZE; i++){
        if(hashSet[i] != 0){
            return false;
        }
    }
    
    return true;
}
