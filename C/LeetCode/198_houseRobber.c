/*
You are a professional robber planning to rob houses along a street.
Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that,
adjacent houses have security system connected and it will automatically contact the police,
if two adjacent houses were broken into on the same night.

Given a list of non-negative integers representing the amount of money of each house,
determine the maximum amount of money you can rob tonight without alerting the police.

Example 1:

Input: nums = [1,2,3,1]
Output: 4
Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
             Total amount you can rob = 1 + 3 = 4.

Example 2:
Input: nums = [2,7,9,3,1]
Output: 12
Explanation: Rob house 1 (money = 2), rob house 3 (money = 9) and rob house 5 (money = 1).
             Total amount you can rob = 2 + 9 + 1 = 12.
 

Constraints:

0 <= nums.length <= 100
0 <= nums[i] <= 400
*/

#include "../standardHeaders.h"

#define max(a,b) ((a) > (b) ? (a) : (b))

/**********************************************************************************************/
/******************************** Solution 1 **************************************************/
/**********************************************************************************************/

int rob(int* nums, int numsSize){
    
    if(numsSize==0)
        return 0;
    
    if(numsSize==1)
        return nums[0];
    
    if(numsSize == 2)
        return max(nums[0], nums[1]);
    
    
    nums[1] = max(nums[0], nums[1]);
    for(int i=2; i<numsSize; i++){
        nums[i] = max(nums[i]+nums[i-2], nums[i-1]);
    }
    
    return nums[numsSize-1];

}

/**********************************************************************************************/
/******************************** Solution 2 **************************************************/
/**********************************************************************************************/

int helper(int* nums, int numsSize){
    if(numsSize == 0)   return 0;
    else if(numsSize==1)     return nums[0];
    else if(numsSize==2)     return max(nums[0],nums[1]);
    
    int dp[3]; // Save only last 3 house in history
    
    /* One house , he will rob it */
    dp[0] = nums[0];    

    /* Two house available, he will rob maximum of it */
    dp[1] = max(nums[0], nums[1]);    
 
    for(int i = 2; i < numsSize; i++) {        
        dp[2] = max(nums[i] + dp[0], dp[1]);
        dp[0] = dp[1];
        dp[1] = dp[2];
    }
    return dp[1];
}

int robBruteForce(int* nums, int numsSize){
    if(numsSize==0){
        return 0;
    }
    if(numsSize==1){
        return nums[0];
    }
    if(numsSize==2){
         return max(nums[0],nums[1]);
    }

    int a=nums[0]+helper(&nums[2],numsSize-2);
    int c=helper(&nums[1],numsSize-1);
    return max(a,c);
}