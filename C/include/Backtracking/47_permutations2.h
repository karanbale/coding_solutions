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

#include "../../standardHeaders.h"

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** permuteUnique(int* nums, int numsSize, int* returnSize, int** returnColumnSizes);
