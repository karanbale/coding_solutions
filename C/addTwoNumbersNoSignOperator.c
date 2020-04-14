/*
Calculate the sum of two integers a and b, but you are not allowed to use the operator + and -.

Example 1:
Input: a = 1, b = 2
Output: 3

Example 2:
Input: a = -2, b = 3
Output: 1

Following solution was obtained from:
https://leetcode.com/problems/sum-of-two-integers/discuss/573229/c-0ms-one-line-address-ofsubscript-operators-simple-and-short/502214
*/

#include "standardHeaders.h"

/*
Here, &((char *)a)[b] is nothing but (a + b) since address-of and subscript operations when applied together, results in no-op and sizeof(char) == 1. 
So, for anyone who might be wondering, there is no illegal memory dereference here.
The only integer types that can correctly represent a generic pointer in C is uintptr_t and intptr_t. 
Thus we need to type cast given integer to uintptr_t -> void * -> char * to access 1 byte of the address.
Rest of the casting in my below solution is for portability and correctness.
*/

int getSum_Method1(int a, int b){
    return (uintptr_t)&((char *)(void *)(uintptr_t)a)[b]; 
}

int main(void){

    int nums[4] = {1,2,INT32_MAX,INT32_MIN};
    for (int i = 0; i < 4; i=i+2)
    {
        printf("Sum of a: %d, b: %d is:\n",nums[i],nums[i+1]);
        printf("Method 1: %d\n",getSum_Method1(nums[i], nums[i+1]));
        printf("\n");
    }
    return 0;
}
