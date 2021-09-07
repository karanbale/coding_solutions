/*
Given the string croakOfFrogs, which represents a combination of the string "croak" from different frogs,
that is, multiple frogs can croak at the same time, so multiple “croak” are mixed.
Return the minimum number of different frogs to finish all the croak in the given string.

A valid "croak" means a frog is printing 5 letters ‘c’, ’r’, ’o’, ’a’, ’k’ sequentially.
The frogs have to print all five letters to finish a croak. If the given string is not a combination of valid "croak" return -1.

Example 1:
Input: croakOfFrogs = "croakcroak"
Output: 1 
Explanation: One frog yelling "croak" twice.

Example 2:
Input: croakOfFrogs = "crcoakroak"
Output: 2 
Explanation: The minimum number of frogs is two. 
The first frog could yell "crcoakroak".
The second frog could yell later "crcoakroak".

Example 3:
Input: croakOfFrogs = "croakcrook"
Output: -1
Explanation: The given string is an invalid combination of "croak" from different frogs.

Example 4:
Input: croakOfFrogs = "croakcroa"
Output: -1

Constraints:

1 <= croakOfFrogs.length <= 10^5
All characters in the string are: 'c', 'r', 'o', 'a' or 'k'.
*/

#include "../standardHeaders.h"

#define max(a, b) ((a) > (b) ? (a) : (b))

// croaking must occur in the order of: 'c' -> 'r' -> 'o' -> 'a -> 'k'
int minNumberOfFrogs(char * croakOfFrogs){
    int croakCount[5] = {0};
    int frogCount = 0, currFrogCount = 0;
    while(*croakOfFrogs) {
        switch(*croakOfFrogs) {
            case 'c':
                // Found first croaking, add a frog count
                currFrogCount++;
                // keep track of frogs
                croakCount[0]++;
                // keep track of max frogs
                frogCount = max(frogCount, currFrogCount);
                break;
            case 'r':
                // if current char is out of order i.e.
                // r ocurred before c
                if (croakCount[0] <= croakCount[1])  return -1;
                croakCount[1]++;
                break;
            case 'o':
                // if current char is out of order i.e.
                // o ocurred before c or r
                if (croakCount[1] <= croakCount[2])  return -1;
                croakCount[2]++;
                break;
            case 'a':
                // if current char is out of order i.e.
                // a ocurred before c, r, or o
                if (croakCount[2] <= croakCount[3])  return -1;
                croakCount[3]++;
                break;
            case 'k':
                // if current char is out of order i.e.
                // k ocurred before c, r, o or a
                if (croakCount[3] <= croakCount[4])  return -1;
                croakCount[4]++;
                currFrogCount--;
                break;
            // Found character that is not in string "croak"
            default:
                return -1;
        }
        croakOfFrogs++;
    }
    
    // Check if freq of all characters is equal
    // if any character occured more or less, that means, some frog did not finish croaking
    int total = croakCount[0];
    for(int i=1; i<5; i++) {
        if (total != croakCount[i]) return -1;
    }
    return frogCount;
}
