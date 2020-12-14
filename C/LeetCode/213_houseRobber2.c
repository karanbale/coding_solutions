/*
You are a professional robber planning to rob houses along a street.
Each house has a certain amount of money stashed. All houses at this place are arranged in a circle.
That means the first house is the neighbor of the last one.
Meanwhile, adjacent houses have a security system connected, and it will automatically contact the police,
if two adjacent houses were broken into on the same night.

Given a list of non-negative integers nums representing the amount of money of each house,
return the maximum amount of money you can rob tonight without alerting the police.

Example 1:
Input: nums = [2,3,2]
Output: 3
Explanation: You cannot rob house 1 (money = 2) and then rob house 3 (money = 2), because they are adjacent houses.

Example 2:
Input: nums = [1,2,3,1]
Output: 4
Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
Total amount you can rob = 1 + 3 = 4.

Example 3:
Input: nums = [0]
Output: 0
 
Constraints:

1 <= nums.length <= 100
0 <= nums[i] <= 1000
*/

#include "../standardHeaders.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b));

int straight_rob(int *nums, int size)
{
    if(size == 1) return nums[0];
    if(size == 2) return MAX(nums[0], nums[1]);
    
    int dp[3]; // Save only last 3 house in history
    
    /* One house , he will rob it */
    dp[0] = nums[0];    

    /* Two house available, he will rob maximum of it */
    dp[1] = MAX(nums[0], nums[1]);    
 
    for(int i = 2; i < size; i++) {        
        dp[2] = MAX(nums[i] + dp[0], dp[1]);
        dp[0] = dp[1];
        dp[1] = dp[2];
    }
    return dp[1];
}

int rob(int* nums, int size)
{
    if(size == 0) {
        /* No house to rob */
        return 0;
    }else if(size == 1) {
        /* One house, he will rob it */
        return nums[0];
    }else{
        /* MAX of [skipping last house] OR [skipping first house] */
        return MAX(straight_rob(nums, size - 1), 
                   straight_rob(nums + 1, size - 1));
    }
}
