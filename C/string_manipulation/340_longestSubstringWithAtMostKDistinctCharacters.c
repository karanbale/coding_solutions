/**
 * Given a string, find the length of the longest substring T that contains at most k distinct characters.
 * Example 1:
 *      Input: s = "eceba", k = 2
 *      Output: 3
 *      Explanation: T is "ece" which its length is 3.
 * 
 * Example 2:
 *      Input: s = "aa", k = 1
 *      Output: 2
 *      Explanation: T is "aa" which its length is 2.
*/

#include "../standardHeaders.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct Set {
    int count[256];
} Set;

void set_add(Set *set, char c)
{
    int n = c;
    set->count[n]++;
}

int set_len(Set *set)
{
    int n = 0;
    int i;
    for (i = 0; i < 256; i++) {
        if (set->count[i] > 0)
            n++;
    }
    return n;
}

void set_remove(Set *set, char c)
{
    int n = c;
    set->count[n]--;
}

int lengthOfLongestSubstringKDistinct(char * s, int k)
{
    // create dummy hash-map 
    Set win;
    // initialize the hash-map to 0
    memset(&win, 0, sizeof(win));
    int i;
    int win_start = 0;
    int n = strlen(s);
    int best = 0;
    
    // start iterating over string s
    for (i = 0; i < n; i++) {
        // take each character of the string s
        char c = s[i];
        // add this character to the hash-map
        set_add(&win, c);
        // if the character count in hash-map exceeds k
        // remove 
        while (set_len(&win) > k) {
            // remove from left
            // win_start points to first valid character in hash-map
            // at any given time
            char d = s[win_start++];
            set_remove(&win, d);
        }
        
        // get the max count between max seen so far and current length - first valid kth element + 1 (due to 0 indexing of array)
        best = MAX(best, i - win_start + 1);
    }
    
    return best;
}

