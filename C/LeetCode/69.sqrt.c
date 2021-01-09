/*
Given a non-negative integer x, compute and return the square root of x.
Since the return type is an integer, the decimal digits are truncated, and only the integer part of the result is returned.

Example 1:
Input: x = 4
Output: 2

Example 2:
Input: x = 8
Output: 2
Explanation: The square root of 8 is 2.82842..., and since the decimal part is truncated, 2 is returned.

Constraints:

0 <= x <= 231 - 1
*/

#include "../standardHeaders.h"


#define SQR(x) ((x)*(x))

int mySqrtSolution1(int x){

    return (int)(pow(2,(0.5*log2(x))));
    
}

int mySqrtSolution2(int x){
    if(x < 2) return x;
    
    int left, right;
    left = 0;
    right = x;
    
    while(left < right){
        int mid = left + (right-left)/2;
        // following line cannot contain mid*mid as (mid*mid), i.e. in round brackets
        // adding round brackes will trunkate the MSB bits of the results
        // yielding wrong value
        unsigned long long int sqr = (unsigned long long int) mid*mid;
        if(sqr > x){
            right = mid;
        }
        else{
            left = mid+1;
        }
    }
    return left-1;
}
