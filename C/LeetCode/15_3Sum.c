/*
Given an array nums of n integers, are there elements a, b, c in nums such that,
a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

Notice that the solution set must not contain duplicate triplets.

Example 1:
Input: nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]

Example 2:
Input: nums = []
Output: []

Example 3:
Input: nums = [0]
Output: []

Constraints:

0 <= nums.length <= 3000
-105 <= nums[i] <= 105

*/

#include "../standardHeaders.h"

int cmp(const void *a, const void *b)
{
    return *(int*)a - *(int*)b;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
    *returnSize = 0;
    if (numsSize < 3) 
        return NULL;
    
    qsort(nums, numsSize, sizeof(nums[0]), cmp);
    
    int **returnArray = (int**)malloc(sizeof(int)*numsSize*(numsSize-1)/2);
    if(!returnArray){
        return NULL;
    }
    
    int left = 0;
    int right = numsSize - 1;
    for(int i = 0;nums[i] <= 0 && i < numsSize-2;){
        left = i+1;
        right = numsSize-1;
        while(left < right){
            int sum = nums[i] + nums[left] + nums[right];
            if(sum > 0){
                right--;
            }
            else if(sum < 0){
                left++;
            }
            else{
                *returnSize += 1;
                returnArray[*returnSize - 1] = malloc(sizeof(int)*3);
                returnArray[*returnSize - 1][0] = nums[i];
                returnArray[*returnSize - 1][1] = nums[left];
                returnArray[*returnSize - 1][2] = nums[right];
                // avoid duplicates
                do right--; while(left < right && nums[right] == nums[right+1]);
            }
        }
        // avoid dupliates
        do i++; while(i < (numsSize-2) && (nums[i] == nums[i-1]));
    }
    
    // printArr(returnArray, retArrIdx, 3);
    *returnColumnSizes = (int*)malloc(sizeof(int)*(*returnSize));
    for (int i = 0; i < *returnSize; i++)
        (*returnColumnSizes)[i] = 3;
    
    return returnArray;

}
