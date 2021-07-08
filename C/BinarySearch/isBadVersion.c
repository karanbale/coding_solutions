/*
You are a product manager and currently leading a team to develop a new product. 
Unfortunately, the latest version of your product fails the quality check. 
Since each version is developed based on the previous version, all the versions after a bad version are also bad.
Suppose you have n versions [1, 2, ..., n] and you want to find out the first bad one, which causes all the following ones to be bad.
You are given an API bool isBadVersion(version) which will return whether version is bad. 
Implement a function to find the first bad version. You should minimize the number of calls to the API.

Example:

Given n = 5, and version = 4 is the first bad version.

call isBadVersion(3) -> false
call isBadVersion(5) -> true
call isBadVersion(4) -> true

Then 4 is the first bad version. 
*/

#include "../standardHeaders.h"

// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

bool isBadVersion(int version){
    int first_invalid_range[4] = {1,2,4,14678976};
    for(int i=0; i<4; i++){
        if(first_invalid_range[i] >= version) return true;
    }
    return false;
}

int firstBadVersion(int n) {
    printf("num: %d\n",n);
    int left = 0, right = n, mid = 0;
    if(n == 0 || n == 1) return n;
    while(left < right){
        printf("mid: %d\t left: %d\t right: %d\n", mid, left, right);
        mid = left + (right - left) / 2;
        if(isBadVersion(mid) == true){
            // if found bad version, make sure its the first one
            // the one before current bad version, must be a good version
            // else your version becomes your right
            if(isBadVersion(mid-1) == false) return mid;
        }
        if(isBadVersion(mid) == false) left = mid + 1;
        else right = mid;
    }
    printf("left is: %d \t mid: %d left_true:%d\n\n",left, mid,isBadVersion(left));
    if(isBadVersion(left) == true) return left;
    return mid;
}

int main(void){
    int input_range[][2] = {{1,1},{2,2},{5,4},{206789765,15678976}};
    return 0;
}

