/*
A string S of lowercase English letters is given.
We want to partition this string into as many parts as possible so that each letter appears in at most one part,
and return a list of integers representing the size of these parts.

Example 1:
Input: S = "ababcbacadefegdehijhklij"
Output: [9,7,8]
Explanation:
The partition is "ababcbaca", "defegde", "hijhklij".
This is a partition so that each letter appears in at most one part.
A partition like "ababcbacadefegde", "hijhklij" is incorrect, because it splits S into less parts.
 
Note:

S will have length in range [1, 500].
S will consist of lowercase English letters ('a' to 'z') only.
*/

#include "../standardHeaders.h"


#define MAX(a, b) ((a) > (b) ? (a) : (b))
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* partitionLabels(char * S, int* returnSize){
    *returnSize = 0;
    if(!strlen(S))  return 0;
    int len = strlen(S);
    int *retArr = (int *) malloc(sizeof(int));
    *returnSize = 0;
    
    int maxIdxArr[26];
    // initialize the entire array to 0
    memset(maxIdxArr, 0, sizeof(int) * 26);
    
    for(int i=0; i<len; i++){
        maxIdxArr[S[i]-97] = i;
    }
    
    int left = 0, right = 0;
    int runTimeIdx = 0;
    for(int i=0; i<strlen(S); i++){
        // take the farthest index for this character
        right = MAX(right, maxIdxArr[S[i]-'a']);
        // reset right if you've found the max so far for previously calculated, this is new subString
        if(right == i){
            (*returnSize)++;
            retArr = realloc(retArr, (*returnSize)*sizeof(int));
            retArr[(*returnSize)-1] = (right-left+1);
            left = right+1;
        }
    }
    
    return retArr;
}