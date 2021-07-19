/*
In an alien language, surprisingly they also use english lowercase letters, but possibly in a different order. The order of the alphabet is some permutation of lowercase letters.
Given a sequence of words written in the alien language, and the order of the alphabet, return true if and only if the given words are sorted lexicographicaly in this alien language.

Example 1:

Input: words = ["hello","leetcode"], order = "hlabcdefgijkmnopqrstuvwxyz"
Output: true
Explanation: As 'h' comes before 'l' in this language, then the sequence is sorted.
Example 2:

Input: words = ["word","world","row"], order = "worldabcefghijkmnpqstuvxyz"
Output: false
Explanation: As 'd' comes after 'l' in this language, then words[0] > words[1], hence the sequence is unsorted.
Example 3:

Input: words = ["apple","app"], order = "abcdefghijklmnopqrstuvwxyz"
Output: false
Explanation: The first three characters "app" match, and the second string is shorter (in size.) According to lexicographical rules "apple" > "app", because 'l' > '∅', where '∅' is defined as the blank character which is less than any other character (More info).
 

Constraints:

1 <= words.length <= 100
1 <= words[i].length <= 20
order.length == 26
All characters in words[i] and order are English lowercase letters.
*/

#include "../standardHeaders.h"

bool isAlienSorted(char ** words, int wordsSize, char * order){
    int hashMap[26] = {0};
    for(int i=0; i<strlen(order); i++) {
        hashMap[order[i]-'a'] = i;
    }
    
    // iterate over all words
    for(int i=0; i<wordsSize-1; i++) {
        // pick the first word
        for(int j=0; j<strlen(words[i]); j++) {
            // compare first two word's first character
            if(words[i][j] != words[i+1][j]) {
                // what if length of 1st word is > length of 2nd word ? e.g. {"apple", "app"}
                // Then words are not sorted, for this case, order of words should have been swapped
                if(j >= strlen(words[i+1])) return false;
                // grab each words rank
                int word1Char1Rank = hashMap[words[i][j]-'a'];
                int word2Char1Rank = hashMap[words[i+1][j]-'a'];
                // if current words char has higer order than next words char, then words are not sorted
                if(word1Char1Rank > word2Char1Rank) {
                    return false;
                }
                // if current words char has lower order than next words char, then words are sorted
                // remmeber, the alphabets are permutation of lowercase letters
                else {
                    break;
                }
            }
        }
    }
    
    return true;
}


bool cmpFunc (char* a, char* b, int* orderTable)
{
    int sizeA = strlen(a);
    int sizeB = strlen(b);
    
    for(int i = 0; i < sizeA && i < sizeB; i++)
    {
        if(orderTable[a[i]-'a'] < orderTable[b[i]-'a']) return true;
        else if(orderTable[a[i]-'a'] > orderTable[b[i]-'a']) return false;
    }
    
    return (sizeA < sizeB);
}

bool isAlienSortedSolution2(char** words, int wordsSize, char* order) {
    int orderTable[26] = {0};
    for(int i = 0; i < 26; i++)
    {
        orderTable[order[i]-'a'] = i;
    }
    for(int i = 0; i < wordsSize-1; i++)
    {
        if(!cmpFunc(words[i], words[i+1], orderTable)) return false;
    }
    return true;
}
