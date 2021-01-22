/*
Given strings S and T, find the minimum (contiguous) substring W of S, so that T is a subsequence of W.
If there is no such window in S that covers all characters in T, return the empty string "".
If there are multiple such minimum-length windows, return the one with the left-most starting index.

Example 1:

Input: 
S = "abcdebdde", T = "bde"
Output: "bcde"
Explanation: 
"bcde" is the answer because it occurs before "bdde" which has the same length.
"deb" is not a smaller window because the elements of T in the window must occur in order.
 

Note:

All the strings in the input will only contain lowercase letters.
The length of S will be in the range [1, 20000].
The length of T will be in the range [1, 100].
*/

#include "../standardHeaders.h"

char * minWindow(char * S, char * T){
    
    int lenOfS = strlen(S);
    int lenOfT = strlen(T);
    
    if(lenOfT > lenOfS)   return "";
    
    int subStrStartIdx = 0, subStrLen = INT32_MAX;
    int retStartIdx = 0;

    // iterate over string S
    for(int endIdx=0; endIdx<lenOfS; endIdx++){
        // reset starting index of T for each character in S
        retStartIdx = 0;
        // if first character of T matches with current character of S
        // lets go down this rabbit hole and find our subString
        if(S[endIdx] == T[retStartIdx]){
            int tempIdx = endIdx;
            // keep iteratin over S from tempIdx until all characters in T are found
            // or until we reach end of S
            while((tempIdx < lenOfS) && (retStartIdx != lenOfT)){
                if(S[tempIdx++] == T[retStartIdx]){
                    retStartIdx++;
                }
            }
            // have we reached end of string T ? if yes, then we've a matchin substring
            if(retStartIdx == lenOfT){
                int tempSubStrLen = tempIdx-endIdx;
                // lets only store this substring if it is smaller than previous substring lengths
                if(tempSubStrLen < subStrLen){
                    subStrLen = tempSubStrLen;
                    subStrStartIdx = endIdx;
                }
            }
            // we've reached end of string S, and still have not found a single substring
            // so let's return empty string, no point in iterating over S
            else if((subStrLen == INT32_MAX) && (tempIdx == lenOfS)){
                return "";
            }
        }
    }
    
    if(subStrLen != INT32_MAX){
        char *retArr = malloc(sizeof(char)*(subStrLen+1));
        strncpy(retArr, S+subStrStartIdx, subStrLen);
        retArr[subStrLen] = '\0';
        return retArr;
    }
    
    return "";
    
}

/*
Sample inputs to test:
"cnhczmccqouqadqtmjjzl"
"mm"
"jmeqksfrsdcmsiwvaovztaqenprpvnbstl"
"u"
"abcdebdde"
"bde"
"cnhczmccqouqadqtmjjzl"
"cm"
*/