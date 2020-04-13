/*
Given a 32-bit signed integer, reverse digits of an integer.

    Example 1:
    Input: 123
    Output: 321

    Example 2:
    Input: -123
    Output: -321

    Example 3:
    Input: 120
    Output: 21

Note:
    Assume we are dealing with an environment which could only store integers, 
    within the 32-bit signed integer range: [−231,  231 − 1]. 
    For the purpose of this problem, assume that your function returns 0 when the reversed integer overflows.

*/

#include "standardHeaders.h"

ssize_t reverse(int x){

    if(x > INT32_MAX || x<INT32_MIN) return 0;
    
    // use ssize_t in order to compute with sign
    ssize_t ret_num = 0;

    while(x){
        ret_num = (ret_num*10) + (x%10);
        x = x/10;
        printf("max: %d, x: %d, ret_num: %ld\n", INT32_MAX, x, ret_num);
    }

    // if reversed number is out of range, return 0
    return ((ret_num > INT32_MAX || ret_num < INT32_MIN) ? 0 : ret_num);
}

int main(void){

    uint32_t nums[6] = {-123, 123, INT32_MIN, INT32_MAX, INT32_MAX+5, 1534236469};

    for (size_t i = 0; i < 6; i++)
    {
        printf("Num: %d Reverse of Num: %ld\n", nums[i], reverse(nums[i]));
    }
    

    return 0;
}