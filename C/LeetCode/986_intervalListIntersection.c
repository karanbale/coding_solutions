/*
Given two lists of closed intervals, each list of intervals is pairwise disjoint and in sorted order.
Return the intersection of these two interval lists.

(Formally, a closed interval [a, b] (with a <= b) denotes the set of real numbers x with a <= x <= b.  
The intersection of two closed intervals is a set of real numbers that is either empty, or can be represented as a closed interval.  
For example, the intersection of [1, 3] and [2, 4] is [2, 3].)

Example 1:

Input: A = [[0,2],[5,10],[13,23],[24,25]], B = [[1,5],[8,12],[15,24],[25,26]]
Output: [[1,2],[5,5],[8,10],[15,23],[24,24],[25,25]]

Note:

0 <= A.length < 1000
0 <= B.length < 1000
0 <= A[i].start, A[i].end, B[i].start, B[i].end < 10^9

*/

#include "../standardHeaders.h"

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

#define MAX(a,b)  ((a > b) ? a : b);
#define MIN(a,b)  ((a < b) ? a : b);

void printArr(int **A, int r, int c){
    for (int i = 0; i <  r; i++){
        printf("[");
        for (int j = 0; j < c; j++){
            printf(" %d ", A[i][j]);
        }
        printf("]\n");
    }
}

int** intervalIntersection(int** A, int ASize, int* AColSize, int** B, int BSize, int* BColSize, int* returnSize, int** returnColumnSizes){
    int maxOverlap = ASize+BSize;
    int** retArr = malloc(sizeof(int*)*maxOverlap);
    int* retColSize = malloc(sizeof(int)*maxOverlap);

    int retArrRowIdx = 0;
    int firstPtr = 0, secondPtr = 0;

    while(firstPtr < ASize && secondPtr < BSize){
        int maxStart = MAX(A[firstPtr][0], B[secondPtr][0]);
        int minEnd = MIN(A[firstPtr][1], B[secondPtr][1]);
        
        if(maxStart <= minEnd){
            // Allocate required memory in run-time, to minimize mem utilization to minimum
            retArr[retArrRowIdx] = malloc(sizeof(int)*2);
            retArr[retArrRowIdx][0] = maxStart;
            retArr[retArrRowIdx][1] = minEnd;
            retColSize[retArrRowIdx] = 2;
            retArrRowIdx++;
        }
        
        if(A[firstPtr][1] < B[secondPtr][1]){
            firstPtr++;
        }
        else{
            secondPtr++;
        }
    }
    
    // printArr(A, ASize,2);
    // printArr(B, BSize,2);
    // printArr(retArr, retArrRowIdx, 2);
    
    *returnColumnSizes = retColSize;
    *returnSize = retArrRowIdx;
    return retArr;
}

