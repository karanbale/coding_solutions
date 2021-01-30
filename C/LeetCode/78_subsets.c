/*
Given an integer array nums of unique elements, return all possible subsets (the power set).
The solution set must not contain duplicate subsets. Return the solution in any order.

Example 1:

Input: nums = [1,2,3]
Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
Example 2:

Input: nums = [0]
Output: [[],[0]]
 
Constraints:

1 <= nums.length <= 10
-10 <= nums[i] <= 10
All the numbers of nums are unique.
*/

#include "../standardHeaders.h"

char *int2bin(int a, char *buffer, int buf_size) {
    buffer += (buf_size);
    *buffer-- = '\0';
    for (int i = buf_size-1; i >= 0; i--) {
        *buffer-- = (a & 1) + '0';

        a >>= 1;
    }

    return buffer+1;
}

static inline int numOf1sInNum(int num){
    int totalOnes = 0;
    while(num){
        num &= (num-1);
        totalOnes++;
    }
    return totalOnes;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** subsets(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
    // max output bits will be 2 ^ numsSize
    int maxBitLen = 1 << numsSize;
    
    *returnSize = 0;
    int **retArr = malloc(maxBitLen*sizeof(int *));
    *returnColumnSizes = malloc(maxBitLen*sizeof(int));
    
    // first output will always be 0, since 0 is a valid combination
    (*returnColumnSizes)[(*returnSize)++] = 0;
    
    for(int i=1; i< maxBitLen; i++){
        int num = i, idx = 0;
        // count total num of 1's in current number, iterate over it
        int size = numOf1sInNum(num);
        
        // store sub array size
        (*returnColumnSizes)[(*returnSize)] = size;
        
        // malloc subarray
        int *tempArr = malloc(sizeof(int)*size);
        int tempArrIdx = 0;
        // store sub array to output
        retArr[(*returnSize)++] = tempArr;
        
        // for every 1 in num's binary representation, store its corresponding
        // value from nums array to output
        while(num){
            if(num & 1){
                tempArr[tempArrIdx++] = nums[idx];
            }
            idx++;
            num = num >> 1;
        }
    }
    return retArr;
}