/*
You are given an integer array A. From some starting index, you can make a series of jumps.
The (1st, 3rd, 5th, ...) jumps in the series are called odd-numbered jumps, and the (2nd, 4th, 6th, ...) jumps in the series are called even-numbered jumps. Note that the jumps are numbered, not the indices.

You may jump forward from index i to index j (with i < j) in the following way:

During odd-numbered jumps (i.e., jumps 1, 3, 5, ...), 
you jump to the index j such that A[i] <= A[j] and A[j] is the smallest possible value. 
If there are multiple such indices j, you can only jump to the smallest such index j.

During even-numbered jumps (i.e., jumps 2, 4, 6, ...),
you jump to the index j such that A[i] >= A[j] and A[j] is the largest possible value.
If there are multiple such indices j, you can only jump to the smallest such index j.

It may be the case that for some index i, there are no legal jumps.

A starting index is good if, starting from that index, you can reach the end of the array (index A.length - 1),
by jumping some number of times (possibly 0 or more than once).

Return the number of good starting indices.

Example 1:
Input: A = [10,13,12,14,15]
Output: 2
Explanation: 
From starting index i = 0, we can make our 1st jump to i = 2 (since A[2] is the smallest among A[1], A[2], A[3],
A[4] that is greater or equal to A[0]), then we cannot jump any more.
From starting index i = 1 and i = 2, we can make our 1st jump to i = 3, then we cannot jump any more.
From starting index i = 3, we can make our 1st jump to i = 4, so we have reached the end.
From starting index i = 4, we have reached the end already.
In total, there are 2 different starting indices i = 3 and i = 4, where we can reach the end with some number of
jumps.

Example 2:
Input: A = [2,3,1,1,4]
Output: 3
Explanation: 
From starting index i = 0, we make jumps to i = 1, i = 2, i = 3:

During our 1st jump (odd-numbered), we first jump to i = 1 because A[1] is the smallest value in [A[1], A[2],
A[3], A[4]] that is greater than or equal to A[0].

During our 2nd jump (even-numbered), we jump from i = 1 to i = 2 because A[2] is the largest value in [A[2], A[3],
A[4]] that is less than or equal to A[1]. A[3] is also the largest value, but 2 is a smaller index, so we can
only jump to i = 2 and not i = 3

During our 3rd jump (odd-numbered), we jump from i = 2 to i = 3 because A[3] is the smallest value in [A[3], A[4]]
that is greater than or equal to A[2].

We can't jump from i = 3 to i = 4, so the starting index i = 0 is not good.

In a similar manner, we can deduce that:
From starting index i = 1, we jump to i = 4, so we reach the end.
From starting index i = 2, we jump to i = 3, and then we can't jump anymore.
From starting index i = 3, we jump to i = 4, so we reach the end.
From starting index i = 4, we are already at the end.
In total, there are 3 different starting indices i = 1, i = 3, and i = 4, where we can reach the end with some
number of jumps.
Example 3:

Input: A = [5,1,3,4,2]
Output: 3
Explanation: 
We can reach the end from starting indices 1, 2, and 4.

Constraints:

1 <= A.length <= 2 * 104
0 <= A[i] < 105
*/

#include "../standardHeaders.h"


int nextEvenJumpIdx(int* A, int ASize, int i){
    int smallestJumpIdx;
    smallestJumpIdx = i;
    if(i >= ASize){
        // printf("\t returning man.......\n");
        return -1;
    }
    
    for (int j=i+1; j < ASize; j++){
        // printf("\t j:%d\n",j);
        // even
        if(A[j] <= A[i]){
            // printf("\t EVEN: BEFORE i:%d j:%d smallestJumpIdx = %d\n", i, j, smallestJumpIdx);
            if(A[smallestJumpIdx] < A[j]){
                // printf("\tChanging smallestJumpIdx to : %d\n", j);
                smallestJumpIdx = j;
            }
            else if(smallestJumpIdx <= i){
                // printf("\tUPDATING smallestJumpIdx to : %d\n", j);
                smallestJumpIdx = j;
            }
            // printf("\t EVEN: AFTER smallestJumpIdx = %d\n", smallestJumpIdx);
        }
    }
    
    if(smallestJumpIdx == i) { return -1; }
    return smallestJumpIdx;
}

int nextOddJumpIdx(int* A, int ASize, int i){
    int smallestJumpIdx = i;
    if(i >= ASize){
        // printf("\t returning man.......\n");
        return -1;
    }
    
    for (int j=i+1; j < ASize; j++){
        // printf("\t j:%d\n",j);
        // odd
        if(A[j] >= A[i]){
            // printf("\t ODD: BEFORE i:%d j:%d smallestJumpIdx = %d\n", i, j, smallestJumpIdx);
            if(A[smallestJumpIdx] > A[j]){
                // printf("\tChanging smallestJumpIdx to : %d\n", j);
                smallestJumpIdx = j;
            }
            else if(smallestJumpIdx <= i){
                // printf("\tUPDATING smallestJumpIdx to : %d\n", j);
                smallestJumpIdx = j;
            }
            // printf("\t ODD: AFTER smallestJumpIdx = %d\n", smallestJumpIdx);
        }
    }
    
    if(smallestJumpIdx == i) { return -1; }
    return smallestJumpIdx;
}

int oddEvenJumps(int* A, int ASize){
    int jump = 0;
    int nextJump = 0;
    int i = 0;
    int j = i+1;
    int total = 0;
    
    for(i=0; i< ASize-1; i++){
        jump = 0;
        j = i;
        // printf("A[i] = %d, Len: %d\n", A[i], ASize);
        for(nextJump = i+1; nextJump < ASize; nextJump++){
            jump++;
            int returnedJumpIdx = -1;
            // printf("A[i]:%d, Jump: %d, Mod: %d\n", A[j], jump, (jump%2));
            // Odd jump
            if((jump == 1) || (jump %2) != 0){
                returnedJumpIdx = nextOddJumpIdx(A, ASize, j);
                j = returnedJumpIdx;
                if((returnedJumpIdx > (ASize-1)) || (returnedJumpIdx == -1)){
                    // printf("----- BREAKING -----\n");
                    break;
                }
                // printf("\t Odd:  A[i] = %d, nextJump: %d\n", A[j], j);
            }
            // Even jump
            else{
                returnedJumpIdx = nextEvenJumpIdx(A, ASize, j);
                j = returnedJumpIdx;
                if((returnedJumpIdx > (ASize-1)) || (returnedJumpIdx == -1)){
                    // printf("----- BREAKING -----\n");
                    break;
                }
                // printf("\t Even: A[i] = %d, nextJump: %d\n", A[j], j);
            }
            if(j == (ASize-1)){
                // printf("##### REACHED ########\n");
                total++;
                break;
            }
        }
    }
    
    return total+1;

}
