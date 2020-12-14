/*
Given an unsorted integer array nums, find the smallest missing positive integer.
Follow up: Could you implement an algorithm that runs in O(n) time and uses constant extra space.?

Example 1:
Input: nums = [1,2,0]
Output: 3

Example 2:
Input: nums = [3,4,-1,1]
Output: 2

Example 3:
Input: nums = [7,8,9,11,12]
Output: 1
 

Constraints:

0 <= nums.length <= 300
-231 <= nums[i] <= 231 - 1
*/

#include "../standardHeaders.h"

int firstMissingPositive(int* nums, int numsSize){
    int *tempArr = calloc(sizeof(int), numsSize+2);
    
    for(int i=0; i<numsSize; i++){
        if((nums[i] > 0) && (nums[i] <= numsSize)){
            tempArr[nums[i]]++;
        }
    }
    
    for(int i=1; i<=numsSize+1; i++){
        if(tempArr[i] == 0){
            return i;
        }
    }
    
    return 1;

}

/*
inputs to test, expected outputs:
[1]             ==> 2
[1,2,0]         ==> 3
[]              ==> 1
*/