/*
Given an array of integers nums sorted in ascending order, find the starting and ending position of a given target value.
If target is not found in the array, return [-1, -1].

Follow up: Could you write an algorithm with O(log n) runtime complexity?

Example 1:
Input: nums = [5,7,7,8,8,10], target = 8
Output: [3,4]

Example 2:
Input: nums = [5,7,7,8,8,10], target = 6
Output: [-1,-1]

Example 3:
Input: nums = [], target = 0
Output: [-1,-1]

Constraints:

0 <= nums.length <= 105
-109 <= nums[i] <= 109
nums is a non-decreasing array.
-109 <= target <= 109

*/

#include "../standardHeaders.h"

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

int* searchRangeSolution1(int* nums, int numsSize, int target, int* returnSize){

    int* range = (int*)malloc(2 * sizeof(int));
    *returnSize = 2;
    range[0] = range[1] = -1;
    int left = 0, right = numsSize;
    int mid;
    
    while (left < right) {
        mid = (left + right) / 2;
        if (nums[mid] < target) {
            left = mid + 1;
        } else if (nums[mid] > target) {
            right = mid;
        } else {
            break;
        }
    }
    
    if (left >= right) return range;
    
    int L = left, R = right, M = mid;
    range[0] = range[1] = mid;
    right = M;
    while (left < right){
        mid = (left + right) / 2;
        if (nums[mid] < target) {
            left = mid + 1;
        }
        else{
            right = mid;
            range[0] = mid;
        }
    }
    
    
    left = M + 1;
    right = R;
    while (left < right){
        mid = (left + right) / 2;
        if (nums[mid] > target) {
            right = mid;
        }
        else {
            left = mid + 1;
            range[1] = mid;
        }
    }
    return range;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

int* searchRangeSolution2(int* nums, int numsSize, int target, int* returnSize){
    
    *returnSize = 2;
    int *retArray = (int *) malloc(sizeof(int) * 2);
    retArray[0] = retArray[1] = -1;
    
    int left, right;
    left = 0;
    right = numsSize-1;
    
    while(left <= right){
        int mid = (right + left)/2;
        if(target > nums[mid]){
            left = mid+1;
        }
        else if(target < nums[mid]){
            right = mid-1;
        }
        else if(nums[mid] == target){
            int nextHighestIdx = mid;
            while(mid>=0 && nums[mid]==target){
                mid--;
            }
            retArray[0] = mid+1;
            while(nextHighestIdx<numsSize && nums[nextHighestIdx]==target){
                nextHighestIdx++;
            }
            retArray[1]=nextHighestIdx-1;
            return retArray;
        }
    }
    return retArray;
}

