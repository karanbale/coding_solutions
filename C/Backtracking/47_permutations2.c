/*
Given a collection of numbers, nums, that might contain duplicates,
return all possible unique permutations in any order.

Example 1:

Input: nums = [1,1,2]
Output:
[[1,1,2],
 [1,2,1],
 [2,1,1]]
Example 2:

Input: nums = [1,2,3]
Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
 

Constraints:

1 <= nums.length <= 8
-10 <= nums[i] <= 10
*/

/*
startIdx: 0, endIdx: 3
	used: [0,0,0,]
startIdx: 1, endIdx: 3
	used: [1,0,0,]
startIdx: 2, endIdx: 3
	used: [1,1,0,]
startIdx: 3, endIdx: 3
	used: [1,1,1,]
returning

startIdx: 2, endIdx: 3
	used: [1,0,1,]
startIdx: 3, endIdx: 3
	used: [1,1,1,]
returning
returning

startIdx: 1, endIdx: 3
	used: [0,0,1,]
startIdx: 2, endIdx: 3
	used: [1,0,1,]
startIdx: 3, endIdx: 3
	used: [1,1,1,]
returning
returning
returning
*/

#include "../standardHeaders.h"

void printArr(int *nums, int numsSize){
    printf("[");
    for(int i=0; i<numsSize; i++){
        printf("%d,",nums[i]);
    }
    printf("]\n");
}

static inline void swap(int *idx1, int *idx2){
    int temp = *idx1;
    *idx1 = *idx2;
    *idx2 = temp;
}

static inline int cmpInt(const void * a, const void * b)
{
    return (*(int*)a - *(int*)b);
}

static inline void backtrack(int ***visited, int *toBeVisited, int startIdx, int endIdx, int* returnSize, int *used, int *temp){
    printArr(used, endIdx);
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
            // (*visited)[*returnSize-1][i] = toBeVisited[i];
            (*visited)[*returnSize-1][i] = temp[i];
        }
        // printf("\tStoring:");
        // printArr(toBeVisited, endIdx);
        return;
    }
    
    // shuffle and deshuffle all the bits, store each shuffled combination
    for(int i = 0; i< endIdx; i++){
        if(used[i]) continue;
        if((i > 0) && (toBeVisited[i-1] == toBeVisited[i]) && (!used[i-1])) continue;
        // shuffle input bit
        // swap(&toBeVisited[startIdx],&toBeVisited[i]);
        used[i] = 1;
        temp[startIdx] = toBeVisited[i];
        // permute again on this shuffled combination
        backtrack(visited, toBeVisited, startIdx+1, endIdx, returnSize, used, temp);
        used[i] = 0;
        // de-shuffle previously shuffled bits
        // swap(&toBeVisited[startIdx],&toBeVisited[i]);
    }
    return;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** permuteUnique(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
    
    *returnSize = 0;
    if(numsSize == 0){
        return NULL;
    }
    
    int **retArr = (int **) malloc(sizeof(int *));
    int *used = (int *) malloc(sizeof(int) * numsSize);
    int *temp = (int *) malloc(sizeof(int) * numsSize);
    memset(used,0,sizeof(int) * numsSize);
    
    qsort(nums, numsSize, sizeof(nums[0]), cmpInt);
    // printf("post sorting\n");
    // printArr(nums, numsSize);
    backtrack(&retArr, nums, 0, numsSize, returnSize, used, temp);
    free(used);

    *returnColumnSizes = (int*)malloc((*returnSize) * sizeof(int));
    for(int i=0; i< *returnSize; i++){
        (*returnColumnSizes)[i] = numsSize;
    }
    
    return retArr;
    
}
