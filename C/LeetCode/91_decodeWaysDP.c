/*
A message containing letters from A-Z can be encoded into numbers using the following mapping:

'A' -> "1"
'B' -> "2"
...
'Z' -> "26"
To decode an encoded message, all the digits must be grouped then mapped back into letters using the reverse of the mapping above (there may be multiple ways). For example, "11106" can be mapped into:

"AAJF" with the grouping (1 1 10 6)
"KJF" with the grouping (11 10 6)
Note that the grouping (1 11 06) is invalid because "06" cannot be mapped into 'F' since "6" is different from "06".

Given a string s containing only digits, return the number of ways to decode it.

The answer is guaranteed to fit in a 32-bit integer.

Example 1:

Input: s = "12"
Output: 2
Explanation: "12" could be decoded as "AB" (1 2) or "L" (12).

Example 2:
Input: s = "226"
Output: 3
Explanation: "226" could be decoded as "BZ" (2 26), "VF" (22 6), or "BBF" (2 2 6).

Example 3:
Input: s = "0"
Output: 0
Explanation: There is no character that is mapped to a number starting with 0.
The only valid mappings with 0 are 'J' -> "10" and 'T' -> "20", neither of which start with 0.
Hence, there are no valid ways to decode this since all digits need to be mapped.

Example 4:
Input: s = "06"
Output: 0
Explanation: "06" cannot be mapped to "F" because of the leading zero ("6" is different from "06").
 

Constraints:

1 <= s.length <= 100
s contains only digits and may contain leading zero(s).
*/

#include "../standardHeaders.h"

int countDecodingWays1(char *s, int sLen, int *dp, int startIdx) {
    int decodingWays = 0;
    int retSingleCharResult;
    // reached end of string, its one way to decode
    if(startIdx == sLen) return 1;
    // encountered zero along the way, go back
    if(s[startIdx] == '0')  return -1;
    if(dp[startIdx] != -1)  return dp[startIdx];
    
    // first keep going down with single character at a time
    retSingleCharResult = countDecodingWays1(s, sLen, dp, startIdx+1);
    if(retSingleCharResult != -1) {
        decodingWays += retSingleCharResult;
    }
    
    // now, keep going down with 2 characters at a time
    if (startIdx+1 < sLen) {
        // form string with 2 characters
        char tempStr[3] = {s[startIdx], s[startIdx+1], '\0'};
        // convert string to number
        int tempNum = atoi(tempStr);
        // make sure this number is between 1 and 26 ie valid character
        if (tempNum > 0 && tempNum < 27) {
            // continue down the rabbit hole with two characters now
            retSingleCharResult = countDecodingWays1(s, sLen, dp, startIdx+2);
            if(retSingleCharResult != -1) {
                // Add results
                decodingWays += retSingleCharResult;
            }
        }
        
    }
    dp[startIdx] = decodingWays;
    return decodingWays;
}

int countDecodingWays2(char *s, int sLen) {
    int dp[sLen+1];
    memset(dp, 0, sizeof(int)*(sLen+1));
    // digit 1 can be decoded in 1 way
    dp[0] = 1;
    // digit 2 can be decoded in 1 way
    dp[1] = 1;
    
    for(int i=2; i<=sLen; i++) {
        // single digit calculation
        if(s[i-1] != '0')   dp[i] += dp[i-1];
        // two digit calculation
        if(s[i-2] == '1' || (s[i-2] == '2' && s[i-1] < '7'))    dp[i] += dp[i-2];
    }
    
    return dp[sLen];
}

int numDecodings(char * s){
    size_t sLen = strlen(s);
    // if number is 0 or starts with 0, return 0
    if((atoi(s) == 0) || (s[0] == '0'))    return 0;
    
    int *dp = (int *) malloc(sizeof(size_t)*sLen);
    memset(dp, -1, sizeof(size_t)*sLen);

    // May receive negative value, which indicates no ways to decode
    // thus return 0 in that case.
    return fmax(countDecodingWays1(s, sLen, dp, 0), 0);
    return countDecodingWays2(s, sLen);
    
}
