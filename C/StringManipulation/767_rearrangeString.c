/*
Given a string S, check if the letters can be rearranged so that two characters that are adjacent to each other are not the same.
If possible, output any possible result.  If not possible, return the empty string.

Example 1:
Input: S = "aab"
Output: "aba"

Example 2:
Input: S = "aaab"
Output: ""

Note:
S will consist of lowercase letters and have length in range [1, 500].
 
*/

#include "../standardHeaders.h"

char * reorganizeString(char * S){
    int l,r,len=strlen(S);
    
    // if found 2 identical in a row, move the right pointer and swap;
    // then move the left pointer as far as possible if no new pair is found
    for(l=0, r=1; r < len; r++)
    {
        while(l < r && S[r] != S[l])
        {
            if(S[l+1] == S[l]) // two in a row
            {
                S[l+1] = S[r]; S[r] = S[l];
            }
            l++;
        }
    }
    if(l+1 == r) return S; // one pass was enough

    // same backwards to handle abb
    for(l = len-1, r = len-1; r >= 0; r--)
    {
        while(l > r && S[r] != S[l])
        {
            if(S[l-1] == S[l]) // two in a row
            {
                S[l-1] = S[r]; S[r] = S[l];
            }
            l--;
        }
    }
    if(l != r+1) S[0]='\0'; // give up and return an empty string
    return S;
}
