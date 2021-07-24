/*
Given an array of integers nums and an integer k, return the total number of continuous subarrays whose sum equals to k.

Example 1:
Input: nums = [1,1,1], k = 2
Output: 2

Example 2:
Input: nums = [1,2,3], k = 3
Output: 2

Constraints:

1 <= nums.length <= 2 * 104
-1000 <= nums[i] <= 1000
-107 <= k <= 107
*/

#include "../standardHeaders.h"

int subarraySum(int* nums, int numsSize, int k){
    int count = 0 ;
    int dp[numsSize+1];
    dp[0] = 0;
    for(int i=1; i<numsSize+1; i++) {
        dp[i] = dp[i-1] + nums[i-1];
    }
    for(int start = 0; start<numsSize; start++) {
        for(int end = start+1; end<numsSize+1; end++) {
            if(dp[end]-dp[start] == k) count++;
        }
    }
    return count;
}
