/*
Given an array nums of n integers and an integer target, are there elements a, b, c, and d in nums such that,
a + b + c + d = target? Find all unique quadruplets in the array which gives the sum of target.

Notice that the solution set must not contain duplicate quadruplets.

Example 1:
Input: nums = [1,0,-1,0,-2,2], target = 0
Output: [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]

Example 2:
Input: nums = [], target = 0
Output: []
 

Constraints:

0 <= nums.length <= 200
-109 <= nums[i] <= 109
-109 <= target <= 109
*/

#include "../standardHeaders.h"

void printArr(int **A, int r, int c){
    for (int i = 0; i <  r; i++){
        printf("[");
        for (int j = 0; j < c; j++){
            printf(" %d ", A[i][j]);
        }
        printf("]\n");
    }
}

int cmp(const void *a, const void *b){
    return *(int *)a - *(int *)b;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** fourSum(int* nums, int numsSize, int target, int* returnSize, int** returnColumnSizes){
    
    qsort(nums, numsSize, sizeof(nums[0]), cmp);
    *returnSize = 0;
    // int **returnArray = NULL;
    int **returnArray = (int**)malloc(sizeof(int)*numsSize*(numsSize-1)/2);
    if(!returnArray)    return NULL;
    
    for(int i=0; i<numsSize-3;i++){
        // avoid duplicates
        if((i>0) && (nums[i] == nums[i-1])){
            continue;
        }
        
        for(int j=i+1; j<numsSize-2;j++){
            if((j>i+1) && (nums[j] == nums[j-1])){
                continue;
            }
            int left = j+1;
            int right = numsSize-1;
            while(left < right){
                int sum = nums[i] + nums[j] + nums[left] + nums[right];
                if(sum > target)    right--;
                else if(sum < target)   left++;
                else{
                    *returnSize += 1;
                    // returnArray= (int **)realloc(returnArray, sizeof(int*)*(*returnSize));
                    returnArray[*returnSize-1] = (int *) malloc(sizeof(int)*4);
                    returnArray[*returnSize-1][0] = nums[i];
                    returnArray[*returnSize-1][1] = nums[j];
                    returnArray[*returnSize-1][2] = nums[left];
                    returnArray[*returnSize-1][3] = nums[right];
                    
                    while((left < right) && (nums[left] == nums[left+1])){
                        left++;
                    }
                    while((left < right) && (nums[right] == nums[right-1])){
                        right--;
                    }
                    left++;
                    right--;
                }
            }
        }
    }
    
    // printArr(returnArray, returnSize, 4);
    *returnColumnSizes = (int*)malloc(*returnSize*sizeof(int));
    for (int i = 0; i < *returnSize; i++)
        (*returnColumnSizes)[i] = 4;
    
    return returnArray;
    
}
