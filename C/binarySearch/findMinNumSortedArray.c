/*

Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e.,  [0,1,2,4,5,6,7] might become  [4,5,6,7,0,1,2]).

Find the minimum element.

You may assume no duplicate exists in the array.

Example 1:

Input: [3,4,5,1,2] 
Output: 1
Example 2:

Input: [4,5,6,7,0,1,2]
Output: 0

*/

#include "../standardHeaders.h"

int findMin(int* nums, int numsSize){
    int smallestNum=INT32_MAX, pivotIndex=-1;
    // find the pivot in the array
    int left = 0, right = numsSize - 1, mid = 0;
    if(numsSize == 1) return nums[0];
    if(nums[numsSize-1] > nums[0]) return nums[0];
    
    while(left <= right){
        // find mid
        mid = left + (right - left) / 2;
        
        // if mid > mid + 1, we've found inflection point at mid + 1
        if(nums[mid] > nums[mid+1]) return nums[mid+1];
        
        // if mid < mid - 1, we've found inflection point at mid
        if(nums[mid] < nums[mid-1]) return nums[mid];
        
        if(nums[mid] > nums[0]) left = mid + 1;
        if(nums[mid] < nums[0]) right = mid - 1;
    }
    return -1;
    
}

int main(void){
    int input_range[][6] = {{1,2,3,4,5,6},{206789765,15678976,2,3,5,6}};
    for(int i=0; i<2; i++){
        printf("Minimum num: %d \n",findMin(input_range[i],6));   
    }
    int input[1] = {1};
    printf("Minimum num: %d \n",findMin(input,6));   
    return 0;
}
