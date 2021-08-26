/*
Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median of the two sorted arrays.

The overall run time complexity should be O(log (m+n)).

Example 1:
Input: nums1 = [1,3], nums2 = [2]
Output: 2.00000
Explanation: merged array = [1,2,3] and median is 2.

Example 2:
Input: nums1 = [1,2], nums2 = [3,4]
Output: 2.50000
Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.

Example 3:
Input: nums1 = [0,0], nums2 = [0,0]
Output: 0.00000

Example 4:
Input: nums1 = [], nums2 = [1]
Output: 1.00000

Example 5:
Input: nums1 = [2], nums2 = []
Output: 2.00000
 

Constraints:

nums1.length == m
nums2.length == n
0 <= m <= 1000
0 <= n <= 1000
1 <= m + n <= 2000
-106 <= nums1[i], nums2[i] <= 106
*/

#include "../standardHeaders.h"

int cmp(void *a, void *b) {
    return *(int *)a - *(int *)b;
}

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size){
    
    int newLen = nums1Size + nums2Size;
    int merged[newLen];
    int idx1 = nums1Size-1;
    int idx2 = nums2Size-1;
    int index = newLen-1;
    while(index >= 0) {
        if(idx1 >= 0 && idx2 >= 0) {
            if(nums1[idx1] < nums2[idx2]) merged[index--] = nums1[idx1--];
            else merged[index--] = nums2[idx2--];
        }
        else if(idx1 >= 0) {
            merged[index--] = nums1[idx1--];
        }
        else if(idx2 >= 0) {
            merged[index--] = nums2[idx2--];
        }
    }

    qsort(merged, newLen, sizeof(merged[0]), cmp);

    double median;
    if(newLen % 2 == 0) {
        median = ((double)merged[newLen/2]+ (double)merged[(newLen/2) - 1])/2;
    }
    else {
        median = (double)merged[newLen/2];
    }
    return median;
}
