
#include "46_permutations.h"
#include "common.h"

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
