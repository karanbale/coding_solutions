/*
Write a program to check whether a given number is an ugly number.
Ugly numbers are positive numbers whose prime factors only include 2, 3, 5.

Example 1:
Input: 6
Output: true
Explanation: 6 = 2 × 3

Example 2:
Input: 8
Output: true
Explanation: 8 = 2 × 2 × 2

Example 3:
Input: 14
Output: false 
Explanation: 14 is not ugly since it includes another prime factor 7.
Note:

1 is typically treated as an ugly number.
Input is within the 32-bit signed integer range: [−231,  231 − 1].
*/

#include "../standardHeaders.h"

bool isUglyMethod1(int num){
    if(num > 0) {
        for(int i=2; i<6; i++) {
            while(0 == (num%i)) num /= i;
        }
    }
    return num == 1;
}

bool isUglyMethod2(int num){
    int temp;
    if(num == 1){
        return true;
    }
    if (num <= 0){
        return false;
    }
    if (num % 2 == 0) { 
        temp = isUgly(num/2);
        if(temp==1){
          return true;
        }
    } 
    if (num % 3 == 0) { 
        temp = isUgly(num/3);
        if(temp==1){
          return true;
        }
    } 
    if (num % 5 == 0) { 
       temp = isUgly(num/5);
       if(temp==1){
          return true;
        }
    } 
    return false; 
}
