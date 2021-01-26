/*
You are given an array of integers nums,
there is a sliding window of size k which is moving from the very left of the array to the very right.
You can only see the k numbers in the window. Each time the sliding window moves right by one position.

Return the max sliding window.

Example 1:

Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
Output: [3,3,5,5,6,7]
Explanation: 
Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
Example 2:

Input: nums = [1], k = 1
Output: [1]
Example 3:

Input: nums = [1,-1], k = 1
Output: [1,-1]
Example 4:

Input: nums = [9,11], k = 2
Output: [11]
Example 5:

Input: nums = [4,-2], k = 2
Output: [4]
 

Constraints:

1 <= nums.length <= 105
-104 <= nums[i] <= 104
1 <= k <= nums.length
*/

#include "../standardHeaders.h"

#define max(a, b) (a > b ? a : b)
int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize){
    
    // maximum number of windows we can have is: numsSize - k + 1
    *returnSize = numsSize - k + 1;
    int* ret = (int*)calloc(sizeof(int), *returnSize);
    
    // take left and right array of size numsSize
    int *left = (int*)calloc(sizeof(int), numsSize);
    int *right = (int*)calloc(sizeof(int), numsSize);
    
    // iterate over entire array
    for (int i = 0; i < numsSize; i++) {
        // every first item of each window, lets take that as max
        // this i is start of each NON-OVERLAPPING window, (slice nums array, k ways, last slice may be smaller than k)
        if (i % k == 0){
            // printf("i: %d\n",i);
            left[i] = nums[i];
        }
        // else take max between current and previous element of current window
        else
            left[i] = max(nums[i], left[i-1]);
        
        // j grows backwards from numsSize-1 upto 0
        int j = numsSize - i - 1;
        // this j is start of each NON-OVERLAPPING window, (slice nums array, k ways, last slice may be smaller than k)
        if ((j + 1) > (numsSize - 1) || ((j+1) % k == 0)){
            // printf("\tj: %d, (j+1)%k : %d, (j+1) > (numsSize-1):%d\n", j, (j+1) % k, (j + 1) > (numsSize - 1));
            right[j] = nums[j];
        }
        // else take max between current and previous element of current window
        else{
            // printf("\tj:%d \n",j);
            right[j] = max(nums[j], right[j+1]);
        }
    }
    // printf("Left: [");
    // for(int i=0; i<numsSize; i++){
    //     printf("%d,",left[i]);
    // }
    // printf("]\n");
    // printf("right: [");
    // for(int i=0; i<numsSize; i++){
    //     printf("%d,",left[i]);
    // }
    // printf("]\n");
    
    // start takin maximum from left and right
    // for left window, you have no calculated a correct max value, until you've reached its last item, 
    // which is at index i+k-1 of first window, so start with an offset of i+k-1
    for (int i = 0; i < *returnSize; i++) {
        ret[i] = max(left[i+k-1], right[i]);
    }
    return ret;    

}
/*
Sample inputs to test:

[1,3,-1,-3,5,3,6,7]
3
answer:
[3,3,5,5,6,7]

[1]
1
answer:
[1]

[1,-1]
1
answer:
[1,-1]

[9,11]
2
answer:
[11]

[4,2]
2
answer:
[4]

*/
