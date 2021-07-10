/*
Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.
If such an arrangement is not possible, it must rearrange it as the lowest possible order (i.e., sorted in ascending order).
The replacement must be in place and use only constant extra memory.


Example 1:
Input: nums = [1,2,3]
Output: [1,3,2]

Example 2:
Input: nums = [3,2,1]
Output: [1,2,3]

Example 3:
Input: nums = [1,1,5]
Output: [1,5,1]

Example 4:
Input: nums = [1]
Output: [1]

Constraints:

1 <= nums.length <= 100
0 <= nums[i] <= 100
*/

#include "../../standardHeaders.h"
int *nextPermutation(int* nums, int numsSize);

/*
Inputs to test:
[1]
[1,1]
[1,2,3]
[3,2,1]
[1,1,5]
[1,5,8,4,7,6,5,3,1]
[1,5,8,5,7,6,4,3,1]
[0,1,2,3,4,5,6,7,8]
[2,3,1,3,3]
[2,1,2,2,2,2,2,1]
*/
