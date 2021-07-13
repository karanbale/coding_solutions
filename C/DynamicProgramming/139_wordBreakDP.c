/*
Given a string s and a dictionary of strings wordDict, return true if s can be segmented into a space-separated sequence of one or more dictionary words.
Note that the same word in the dictionary may be reused multiple times in the segmentation.

Example 1:

Input: s = "leetcode", wordDict = ["leet","code"]
Output: true
Explanation: Return true because "leetcode" can be segmented as "leet code".
Example 2:

Input: s = "applepenapple", wordDict = ["apple","pen"]
Output: true
Explanation: Return true because "applepenapple" can be segmented as "apple pen apple".
Note that you are allowed to reuse a dictionary word.
Example 3:

Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
Output: false
 

Constraints:

1 <= s.length <= 300
1 <= wordDict.length <= 1000
1 <= wordDict[i].length <= 20
s and wordDict[i] consist of only lowercase English letters.
All the strings of wordDict are unique.

*/

#include "../standardHeaders.h"

bool breakWordsRecursive(int *dp, char *s, int sLen, char **wordDict, int wordDictSize, int startIdx) {
    // reached end of string, we found all matches
    if(!s[startIdx])    return true;
    // word is already seen, just skip re-doing work related to searching this word
    if(dp[startIdx] != -1) {
        return dp[startIdx];
    }
    // iterate over given dictionary
    for(int i=0; i<wordDictSize; i++) {
        // pick 1 word out of dictionary at a time
        int len = strlen(wordDict[i]);
        // check if this word is found in string, if not found, just move on
        if(strncmp(s+startIdx, wordDict[i], len) != 0) {
            continue;
        }
        // dictionary word found in string s, lets break it further
        if(breakWordsRecursive(dp, s, sLen, wordDict, wordDictSize, startIdx+len)) {
            dp[startIdx] = true;
            return dp[startIdx];
        }
    }
    // found nothing, set false and return
    dp[startIdx] = false;
    return dp[startIdx];
}

bool wordBreak(char * s, char ** wordDict, int wordDictSize)
{
    int sLen = strlen(s);
    int *dp = (int *) malloc(sizeof(int)*sLen);
    memset(dp, -1, sizeof(int)*sLen);
    bool ret = breakWordsRecursive(dp,s, sLen, wordDict, wordDictSize, 0);
    free(dp);
    return ret;
}
