/*
Given an integer array nums, find the contiguous subarray within an array (containing at least one number) which has the largest product.

Example 1:
Input: [2,3,-2,4]
Output: 6
Explanation: [2,3] has the largest product 6.

Example 2:
Input: [-2,0,-1]
Output: 0
Explanation: The result cannot be 2, because [-2,-1] is not a subarray.
*/

#include "../standardHeaders.h"

int maxProduct(int* nums, int numsSize){
    if(numsSize == 1){
        return nums[0];
    }
    int maxSoFar = nums[0];
    int minSoFar = nums[0];
    int retNum = maxSoFar;
    
    for(int i=1; i<numsSize; i++){
        int curr = nums[i];
        
        int tempMax = fmax(curr, curr*maxSoFar);
        int tempMax1 = fmax(tempMax, curr*minSoFar);
        
        int tempMin = fmin(curr, curr*maxSoFar);
        minSoFar = fmin(tempMin, curr*minSoFar);
        
        maxSoFar = tempMax1;
        
        retNum = fmax(retNum, maxSoFar);
    }
    
    return retNum;

}
