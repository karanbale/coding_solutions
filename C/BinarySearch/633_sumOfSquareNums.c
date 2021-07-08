/*
Given a non-negative integer c, decide whether there're two integers a and b such that a2 + b2 = c.

Example 1:
Input: c = 5
Output: true
Explanation: 1 * 1 + 2 * 2 = 5

Example 2:
Input: c = 3
Output: false

Example 3:
Input: c = 4
Output: true

Example 4:
Input: c = 2
Output: true

Example 5:
Input: c = 1
Output: true

Constraints:

0 <= c <= 231 - 1

*/

#include "../standardHeaders.h"

bool isPerfectSquare(int num){
    if(num < 2) return true;
    
    int left, right;
    
    left = 0;
    right = num;
    
    while(left < right){
        int mid = left + (right - left) / 2;
        double sqr = (double)mid*mid;
        if(sqr == num){
            return true;
        }
        if(sqr > num){
            right = mid;
        }
        else{
            left = mid+1;
        }
    }
    
    return false;
}

bool judgeSquareSumSolution1(int c){
    
    if(c < 3) return true;
    
    unsigned int s1;

    for(int i=0; (double)i*i < c; i++){
        unsigned long long int bSqr = (unsigned long long int)i*i;
        unsigned long long int a = c - bSqr;
        if(isPerfectSquare(a)){
            return true;
        }
    }
    return false;
}

bool judgeSquareSumSolution2(int c) {
    long temp;
    for(long i = 0, j = 0; temp = i*i, temp<= c; i++)
    {
        j = sqrt(c - temp);
        if(temp+j*j == c) return true;
    }
    return false;
}
