/*
Given an array nums of distinct integers, return all the possible permutations.
You can return the answer in any order.

Example 1:
Input: nums = [1,2,3]
Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]

Example 2:
Input: nums = [0,1]
Output: [[0,1],[1,0]]

Example 3:
Input: nums = [1]
Output: [[1]]
 
Constraints:

1 <= nums.length <= 6
-10 <= nums[i] <= 10
All the integers of nums are unique.
*/

/*
Time complexity Analysis:
    Since we're drilling down on each value of n and perform n! computations, the time complexity is:
    (n x n!), however for each n, size of n shrinks (we go from n to n-1 to n-2 etc upto 0)
    so time complexity is slightly better than (n x n!) but worse than (n!)

Space Complexity Analysis: 
    Space complexity is n! since in the output we will have n! sub-arrays for given array of size n.
*/

#include "../standardHeaders.h"

void swap(int *idx1, int *idx2){
    int temp = *idx1;
    *idx1 = *idx2;
    *idx2 = temp;
}

void backtrack(int ***visited, int *toBeVisited, int startIdx, int endIdx, int* returnSize){
    // end condition met, store this shuffled combination
    if(startIdx == endIdx){
        (*returnSize)++;
        // add toBeVisited to visited list
        int newSize = ((*returnSize))*sizeof(int *);
        *visited = (int **) realloc(*visited, newSize);
        (*visited)[*returnSize-1] = (int *) malloc(sizeof(int)*endIdx);
        // for permutation, you will have all inputs just shuffled around
        // thus store all of current shuffled toBeVisited nodes
        for(int i=0; i< endIdx; i++){
            (*visited)[*returnSize-1][i] = toBeVisited[i];
        }
        return;
    }
    
    // shuffle and deshuffle all the bits, store each shuffled combination
    for(int i = startIdx; i< endIdx; i++){
        // shuffle input bit
        swap(&toBeVisited[startIdx],&toBeVisited[i]);
        // permute again on this shuffled combination
        backtrack(visited, toBeVisited, startIdx+1, endIdx, returnSize);
        // deshuffle previously shuffled bits
        swap(&toBeVisited[startIdx],&toBeVisited[i]);
    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** permute(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
    
    if(numsSize == 0){
        *returnSize = 0;
        return NULL;
    }
    
    int **retArr = (int **) malloc(sizeof(int *));

    *returnSize = 0;
    backtrack(&retArr, nums, 0, numsSize, returnSize);

    *returnColumnSizes = (int*) malloc(*returnSize * sizeof(int));
    for(int i=0; i< *returnSize; i++){
        (*returnColumnSizes)[i] = numsSize;
    }
    
    return retArr;
}
