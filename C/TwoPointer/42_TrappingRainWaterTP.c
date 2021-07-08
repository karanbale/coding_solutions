 
 
 // Solution using two pointer approach
int trap(int* height, int heightSize){
    if(0 == heightSize) {
        return 0;
    }
    int ans = 0;
    int leftMax = 0, rightMax = 0;
    int left = 0;
    int right = heightSize-1;
    while(left < right) {
        if(height[left] < height[right]) {
            if(height[left] >= leftMax) {
                leftMax = height[left];
            }
            else {
                ans += (leftMax - height[left]);
            }
            left++;
        }
        else {
            if(height[right] >= rightMax) {
                rightMax = height[right];
            }
            else {
                ans += (rightMax - height[right]);
            }
            right--;
        }
    }
    return ans;
}

void runAlgo(int *waterHeightArr, int size) {
    printf("Water level: %d\n", trap(waterHeightArr, size));
}

int main(void) {
    int waterHeightArr[] = {0,1,0,2,1,0,1,3,2,1,2,1};
    runAlgo(&waterHeightArr, sizeof(waterHeightArr)/sizeof(waterHeightArr[0]));
    int waterHeightArr1[1] = {};
    runAlgo(&waterHeightArr1, 1);
    return 0;
}
