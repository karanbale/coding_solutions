/**
 * Given an array of non-negative integers arr, you are initially positioned at start index of the array. 
 * When you are at index i, you can jump to i + arr[i] or i - arr[i], check if you can reach to any index with value 0.
 * Notice that you can not jump outside of the array at any time.
 * 
 * Example 1:
 *      Input: arr = [4,2,3,0,3,1,2], start = 5
 *      Output: true
 *      Explanation: 
 *          All possible ways to reach at index 3 with value 0 are: 
 *          index 5 -> index 4 -> index 1 -> index 3 
 *          index 5 -> index 6 -> index 4 -> index 1 -> index 3 
 * 
 * Example 2:
 *      Input: arr = [4,2,3,0,3,1,2], start = 0
 *      Output: true 
 *      Explanation:    
 *          One possible way to reach at index 3 with value 0 is: 
 *          index 0 -> index 4 -> index 1 -> index 3
 * 
 * Example 3:
 *      Input: arr = [3,0,2,1,2], start = 2
 *      Output: false
 *      Explanation: There is no way to reach at index 1 with value 0.
 * 
 * Constraints:
 *      1 <= arr.length <= 5 * 10^4
 *      0 <= arr[i] < arr.length
 *      0 <= start < arr.length
 * 
*/

#include "../standardHeaders.h"

// clarifications:
// array can have 1 value
// array must have 0 as a value in it
// if cannot jump, return 0
// length of array = 10^4
// all array elements are >= 0 < array length
// 0 can occur anywhere in the array

bool helper(int *arr, int arrSize, int start, bool *visit){
    bool d1 = false, d2 = false;
    
    if(visit[start] == true){
        return false;
    }
    visit[start] = true;
    if(arr[start] == 0) return true;
    
    if(start+arr[start] < arrSize){
        d1 = helper(arr, arrSize, start+arr[start], visit);
    }
    if(start-arr[start] >= 0){
        d2 = helper(arr, arrSize, start-arr[start], visit);
    }
    // d1 = helper(arr, arrSize, start+arr[start], visit);
    // d2 = helper(arr, arrSize, start-arr[start], visit);
    
    return d1 | d2;
}


bool canReach(int* arr, int arrSize, int start){
    
    // traverse entire array, dont stop until last element is done
    bool visit[50000] = {false};
    bool d1 = helper(arr, arrSize, start, visit);
    return d1;
}

