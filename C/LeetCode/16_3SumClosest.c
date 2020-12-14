/*
Given an array nums of n integers and an integer target, find three integers in nums such that,
the sum is closest to target. Return the sum of the three integers. You may assume that each input would have exactly one solution.

Example 1:
Input: nums = [-1,2,1,-4], target = 1
Output: 2
Explanation: The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
 

Constraints:

3 <= nums.length <= 10^3
-10^3 <= nums[i] <= 10^3
-10^4 <= target <= 10^4
*/

#include "../standardHeaders.h"

int cmp(const void *a, const void *b){
    return *(int *)a - *(int *)b;
}

/**********************************************************************************************/
/******************************** Solution 1 **************************************************/
/**********************************************************************************************/
int threeSumClosest(int* nums, int numsSize, int target){

    int maxDiff = INT32_MAX;
    int retSum = 0;

    qsort(nums, numsSize, sizeof(nums[0]), cmp);

    for(int i=0; i<numsSize; i++){
        int left = i+1, right = numsSize-1;
        while(left < right){
            int sum = nums[i] + nums[left] + nums[right];
            if(abs(target-sum) < maxDiff){
                retSum = sum;
                maxDiff = abs(target-sum);
            }
            if(sum < target){           // sum < target
                left++;
            }
            else if(sum > target){      // sum > target
                right--;
            }
            else{                       // sum = 0
                return retSum;
            }
        }
    }
    return retSum;
    
}

/**********************************************************************************************/
/******************************** Solution 2 **************************************************/
/**********************************************************************************************/

int threeSumClosestUsingTwoSum(int* nums, int numsSize, int target) {
    qsort(nums, numsSize, sizeof(int), cmp);

    int minDiff = INT32_MAX;
    int sum;
    for(int i=0; i<numsSize-2; i++)
    {
        int l, r, delta, twoSum;
        l = i+1;
        r = numsSize-1;
        // a+b+c|d -> a+b|d-c; delta is d-c; twoSum is a+b 
        delta = target - nums[i];
        
        while(l < r)
        {
            twoSum = nums[l] + nums[r];
            int diff = twoSum - delta;
            if(abs(diff) <= minDiff)
            {
                minDiff = abs(diff);
                sum = twoSum + nums[i];
            }
            
            if(!diff)
                return target;
            else if(diff < 0)
                l++;
            else
                r--;
        }
        
    }
    return sum;
    
}