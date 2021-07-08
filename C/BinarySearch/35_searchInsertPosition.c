/*
Given a sorted array of distinct integers and a target value, return the index if the target is found.
If not, return the index where it would be if it were inserted in order.

Example 1:
Input: nums = [1,3,5,6], target = 5
Output: 2

Example 2:
Input: nums = [1,3,5,6], target = 2
Output: 1

Example 3:
Input: nums = [1,3,5,6], target = 7
Output: 4

Example 4:
Input: nums = [1,3,5,6], target = 0
Output: 0

Example 5:
Input: nums = [1], target = 0
Output: 0
 
Constraints:

1 <= nums.length <= 104
-104 <= nums[i] <= 104
nums contains distinct values sorted in ascending order.
-104 <= target <= 104

*/

#include "../standardHeaders.h"

int searchInsert(int* nums, int numsSize, int target){
    int left, right;
    left = 0;
    right = numsSize-1;
    int mid, possibleIndex = 0;
    // printf("target: %d\n", target);
    while(left <= right){
        mid = left + (right - left)/2;
        if(nums[mid] == target){
            return mid;
        }
        else if(target > nums[mid]){            
            left = mid + 1;
        }
        else if(target < nums[mid]){
            right = mid - 1;
        }
    }
    
    // printf("left: %d, right: %d, mid: %d\n", left, right, mid);

    /*
    The loop will be stopped when left <= right and nums[right] < target < nums[left].
    Hence, the proper position to insert the target is at the index left.
    */
    return left;
}
