/*

Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1 as one sorted array.

Note:

The number of elements initialized in nums1 and nums2 are m and n respectively.
You may assume that nums1 has enough space (size that is equal to m + n) to hold additional elements from nums2.
Example:

Input:
nums1 = [1,2,3,0,0,0], m = 3
nums2 = [2,5,6],       n = 3
Output: [1,2,2,3,5,6]
 
Constraints:

-10^9 <= nums1[i], nums2[i] <= 10^9
nums1.length == m + n
nums2.length == n

*/

#include "../standardHeaders.h"

int *merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n){
    
    int nums1Len = m-1;
    int nums2Len = n-1;
    int outArrLen = m+n-1;
    
    while(outArrLen>=0){
        if(nums1Len >= 0 && nums2Len >= 0){
            if(nums1[nums1Len] < nums2[nums2Len]){
                nums1[outArrLen--] = nums2[nums2Len--];
            }
            else{
                nums1[outArrLen--] = nums1[nums1Len--];
            }
        }
        else if(nums1Len >= 0){
            nums1[outArrLen--] = nums1[nums1Len--];
        }
        else if(nums2Len >= 0){
            nums1[outArrLen--] = nums2[nums2Len--];
        }
    }
    
    return nums1;
}