/*
Given an array of non-negative integers, you are initially positioned at the first index of the array.
Each element in the array represents your maximum jump length at that position.
Determine if you are able to reach the last index.

Example 1:
Input: nums = [2,3,1,1,4]
Output: true
Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.

Example 2:
Input: nums = [3,2,1,0,4]
Output: false
Explanation: You will always arrive at index 3 no matter what. Its maximum jump length is 0, which makes it impossible to reach the last index.
 
Constraints:

1 <= nums.length <= 3 * 10^4
0 <= nums[i][j] <= 10^5
*/

#include "../standardHeaders.h"

/**********************************************************************************************/
/******************************** Solution 1 **************************************************/
/**********************************************************************************************/
/**
 * Keep calculating max at each step, 
*/
#define max(a,b) (((a)>(b)) ? (a) : (b))

bool canJumpMethod1(int* nums, int numsSize){
    if(numsSize == 1){
        return true;
    }
	int count = 0;
    // jump can be calculated as: i < jump <= i + nums[i]
    // 
    for(int i=0; i<numsSize; i++){
        if(i > count){
            return false;
        }
        count = max(count, i+nums[i]);
    }
    return true;
}

/**********************************************************************************************/
/******************************** Solution 2 **************************************************/
/**********************************************************************************************/

bool canJumpMethod2(int* nums, int numsSize){
	int lastPos = numsSize-1;
	for(int i = lastPos-1; i >= 0; i--){
		if(i + nums[i] >= lastPos)
			lastPos = i;
	}
	return lastPos == 0;
}
