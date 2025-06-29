/*
Given an integer array nums, find the contiguous subarray (containing at least one number) which has the largest sum and return its sum.

Example 1:
Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
Output: 6
Explanation: [4,-1,2,1] has the largest sum = 6.

Example 2:
Input: nums = [1]
Output: 1

Example 3:
Input: nums = [0]
Output: 0

Example 4:
Input: nums = [-1]
Output: -1

Example 5:
Input: nums = [-100000]
Output: -100000

Constraints:

1 <= nums.length <= 3 * 104
-105 <= nums[i] <= 105
 

Follow up: If you have figured out the O(n) solution, try coding another solution using the divide and conquer approach, which is more subtle.
*/

#include "../standardHeaders.h"


#define MAX(A,B) ((A) > (B) ? (A) : (B))

int maxSubArray(int* nums, int numsSize){
    
    if(numsSize == 1){
        return nums[0];
    }
    
    int dp[numsSize];
    for(int i=1; i<numsSize; i++){
        dp[i] = INT32_MIN;
    } 
    
    dp[0] = nums[0];
    int retNum = nums[0];
    
    for(int i=1; i<numsSize; i++){
        dp[i] = MAX(nums[i], dp[i-1]+nums[i]);
        retNum = MAX(retNum, dp[i]);
    }
    
    return retNum;

}

int maxSubArray2(int* nums, int numsSize){
    
    if(numsSize == 1) {
        return nums[0];
    }

    int max = nums[0];
    int currentSum = nums[0];
    for(int i=1; i<numsSize; i++) {
        if(currentSum < 0) currentSum = 0;
        currentSum += nums[i];
        max = MAX(max, currentSum);
    }
    return max;
}

/*
Inputs to test:
[-2,1]
[-2,1,-3,4,-1,2,1,-5,4]
[1]
[1,2]
[1,2,3]
*/
