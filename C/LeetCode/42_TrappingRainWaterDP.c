/*
Given n non-negative integers representing an elevation map where,
the width of each bar is 1, compute how much water it can trap after raining.
Example 1:
Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
Explanation: The above elevation map (black section) is represented by array,
[0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped.
Example 2:
Input: height = [4,2,0,3,2,5]
Output: 9
 
Constraints:
n == height.length
0 <= n <= 3 * 104
0 <= height[i] <= 105
*/

#include "../StandardHeaders.h"

#define ENABLE_PRINTS 0
#define TM_PRINTF(f_, ...) ENABLE_PRINTS? printf((f_), ##__VA_ARGS__) : 0

int trap(int* height, int heightSize){
    int ans = 0;
    int leftMax[heightSize], rightMax[heightSize];
    leftMax[0] = height[0];
    rightMax[heightSize-1] = height[heightSize-1];
    for(int i=1; i<heightSize; i++) {
        leftMax[i] = MAX(height[i], leftMax[i-1]);
    }
    for(int i=heightSize-2; i>=0; i--) {
        rightMax[i] = MAX(height[i], rightMax[i+1]);
    }
    for(int i =1; i<heightSize-1; i++) {
        ans += MIN(leftMax[i], rightMax[i]) - height[i];
    }
    return ans;
}

void runAlgo(int *waterHeightArr, int size) {
    printf("Water level: %d\n", trap(waterHeightArr, size));
}

int main(void) {
    // int *waterHeightArr = (int *) malloc(sizeof(int) * 12);
    int waterHeightArr[] = {0,1,0,2,1,0,1,3,2,1,2,1};
    runAlgo(waterHeightArr, sizeof(waterHeightArr)/sizeof(waterHeightArr[0]));
    int waterHeightArr1[1] = {};
    runAlgo(waterHeightArr1, 1);
    return 0;
}
