/*
Given a positive integer num, write a function which returns True if num is a perfect square else False.
Follow up: Do not use any built-in library function such as sqrt.

Example 1:
Input: num = 16
Output: true

Example 2:
Input: num = 14
Output: false

Constraints:

1 <= num <= 2^31 - 1
*/

#include "../standardHeaders.h"

bool isPerfectSquare(int num){
    
    if(num < 2) return true;
    
    int left, right;
    
    left = 0;
    right = num;
    
    while(left <= right){
        int mid = left + (right - left) / 2;
        double sqr = (double)mid*mid;
        if(sqr == num){
            return true;
        }
        if(sqr > num){
            right = mid-1;
        }
        else{
            left = mid+1;
        }
    }
    
    return false;
}
