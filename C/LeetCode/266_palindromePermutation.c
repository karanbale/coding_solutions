/*
Given a string, determine if a permutation of the string could form a palindrome.

Example 1:
Input: "code"
Output: false

Example 2:
Input: "aab"
Output: true

Example 3:
Input: "carerac"
Output: true
*/


#include "../standardHeaders.h"

/*
Theory of operation:
    For a number to be palindrome following conditions have to be met.
        1. There need to be even number of occurances of all the characters. e.g. "abccba"
        2. There can only be 1 odd character around which, remaining even numbered characters are organized.
            e.g. "racecar"
*/

bool canPermutePalindrome(char * s){
    
    // allocate an array of size 256 (we have around 256 different characters)
    // initialize this array to a size of 0
    int tempArr[256] = {0};
    
    // for each character, go to its index and increment its value by 1
    // essentially we're just tracking how many times we've seen this number
    for(int i=0; i<strlen(s); i++){
        tempArr[(int)s[i]]++;
    }
    
    // seen odd character
    bool seen_odd = false;
    
    for(int i=0; i<256; i++){
        // if there is odd number of occurance of a character
        if(tempArr[i] %2 != 0){
            // ensure you've not seen a character so far that has odd number of occurances
            if(!seen_odd){
                // mark that we've seen the odd once, and if we see it again, we return false
                seen_odd = true;
            }
            // we've already seen a character with odd number of occurances before, stop now
            else{
                return false;
            }
        }
    }
    return true;

}