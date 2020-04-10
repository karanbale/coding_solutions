/*
Given a number, check if its a power of 2 or not.
Note: You cannot use looping or branching.

Method 1:
Property to remember: 
    Number and its negative representation,
    both will always have it right most set bit same, all other 
    bits will be flipped.

Property of numbers who are power of 2:
    Only 1 bit will be set for numbers, who are power of 2.

Theory of operation for negative numbers:
    To save negative numbers, we flip all the bits of number,
    then we add 1 to it. Hence right most bit of both, will always be same.

E.g.
Number = 12
+(Num) = 0b00001010 (12)
-(Num) = 0b11110110 (-12)
 (ANS) = 0b00000010 (2)

Number = 8
+(Num) = 0b00001000 (8)
-(Num) = 0b11111000 (-8)
 (ANS) = 0b00001000 (8)

*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <stdarg.h>

#define EVEN_ODD_METHOD_1(x) ((x)&(-(x)))
#define ARR_LEN 5

int main(void){

    int num[ARR_LEN] = {5,4,1,0,8};

    for(int i=0; i<ARR_LEN; i++){
        // if ANDing of a number and its negative counterpart is equal to the number itself,
        // then given number is always power of 2
        if(EVEN_ODD_METHOD_1(num[i]) == num[i])  printf("Num: %d is power of 2.\n", num[i]);
        else printf("Num: %d is NOT power of 2.\n", num[i]);

    }

    return 0;
}
