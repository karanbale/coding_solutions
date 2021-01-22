/*
Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.
If such an arrangement is not possible, it must rearrange it as the lowest possible order (i.e., sorted in ascending order).
The replacement must be in place and use only constant extra memory.


Example 1:
Input: nums = [1,2,3]
Output: [1,3,2]

Example 2:
Input: nums = [3,2,1]
Output: [1,2,3]

Example 3:
Input: nums = [1,1,5]
Output: [1,5,1]

Example 4:
Input: nums = [1]
Output: [1]

Constraints:

1 <= nums.length <= 100
0 <= nums[i] <= 100
*/

#include "../standardHeaders.h"

void printArr(int *nums, int numsSize){
    printf("[");
    for(int i=0; i<numsSize; i++){
        printf("%d,", nums[i]);
    }
    printf("]\n");
}

static inline void swap(int *a, int *b){
    int temp = *a; *a = *b; *b = temp;
}

static inline void bubble_sort(int *nums, int start, int end)
{
    for(int i=end; i>=start; i--){
        int has_sorted = 0;
        for(int j=start; j<i; j++){
            if(nums[j] > nums[j+1]){
                swap(&nums[j], &nums[j+1]);
                has_sorted = 1;
            }
        }
        if(has_sorted == 0){
            break;
        }
    }
}

void nextPermutation(int* nums, int numsSize){
    
    // scan nums from right to left
    // find first irregularity i.e. a[i] > a[i-1]
    // NOTE: everything to the right of a[i-1] is sorted, since we could not find any a[i-1] < a[i]
    // start looking to the right of a[i-1] and find next closest but slightly bigger element to a[i-1], lets call it a[j]
    // swap, a[j] and a[i-1] ==> NOTE: This swapping may affect current order on the right hand side of a[i-1]
    // reverse all the numbers after a[i-1], as long as there are no duplicates, and only reverse if first element > last element (swapping first smaller element with last bigger element will enerate a bigger overall array permutation, not what we want)
    // answer is now smallest possible next permutation
    
    int firstIrregularIdx = -1;
    for(int right = numsSize-1; right > 0; right--){
        // found first irregularity, stop
        if(nums[right] > nums[right-1]){
            firstIrregularIdx = right-1;
            break;
        }
    }
    
    // Entire input is in sorted ascending format, just reverse/sort entire array and return
    if(firstIrregularIdx == -1){
        int startIdx = firstIrregularIdx+1;
        int endIdx = numsSize-1;
        bubble_sort(nums, startIdx, endIdx);
    }
    else{
        // start looking to the right of a[i-1] and find next closest but sligghtly bigger element to a[i-1], lets call it a[j]
        int currIrregularNumber = nums[firstIrregularIdx];
        int currentClosestElementIdx = -1, currentDiff = INT32_MAX;
        for(int i=firstIrregularIdx+1; i < numsSize; i++){
            // Logic to avoid duplicates
            if(nums[i] == nums[i-1]) continue;
            int diff = nums[i] - currIrregularNumber;
            if(diff > 0 && currentDiff > diff){
                currentDiff = diff;
                currentClosestElementIdx = i;
            }
        }
        // swap, a[j] and a[i-1]
        swap(&nums[firstIrregularIdx],&nums[currentClosestElementIdx]);
        
        // reverse all the numbers after a[i-1]
        int startIdx = firstIrregularIdx+1;
        if(startIdx < numsSize){
            int endIdx = numsSize-1;
            bubble_sort(nums, startIdx, endIdx);
        }
    }
    return nums;
}

/*
Inputs to test:
[1]
[1,1]
[1,2,3]
[3,2,1]
[1,1,5]
[1,5,8,4,7,6,5,3,1]
[1,5,8,5,7,6,4,3,1]
[0,1,2,3,4,5,6,7,8]
[2,3,1,3,3]
[2,1,2,2,2,2,2,1]
*/