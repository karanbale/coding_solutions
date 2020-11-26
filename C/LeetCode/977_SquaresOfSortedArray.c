/*
Given an array of integers A sorted in non-decreasing order, return an array of the squares of each number, 
also in sorted non-decreasing order.

Example 1:
Input: [-4,-1,0,3,10]
Output: [0,1,9,16,100]

Example 2:
Input: [-7,-3,2,3,11]
Output: [4,9,9,49,121]

Note:

1 <= A.length <= 10000
-10000 <= A[i] <= 10000
A is sorted in non-decreasing order.
*/


#include "../standardHeaders.h"

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

void printArr(int *A, int ASize){
    printf("[");
    for(int i=0; i<ASize; i++){
        printf("%d, ", A[i]);
    }
    printf("]\n");
}

int cmp(const void *str1, const void *str2){
    return (*(int *)str1 - *(int *)str2);
}

int* sortedSquares(int* A, int ASize, int* returnSize){
    
    for(int i=0; i<ASize; i++){
        if(A[i] < 0){
            A[i] = A[i]*(-1);
        }
    }
    
    // printArr(A, ASize);
    qsort(A, ASize, sizeof(int), cmp);
    // printArr(A, ASize);
    
    for(int i=0; i<ASize; i++){
        A[i] = A[i]*A[i];
    }
    
    return *returnSize = ASize, A;
}