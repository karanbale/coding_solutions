#include "47_permutations2.h"
#include "common.h"

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
