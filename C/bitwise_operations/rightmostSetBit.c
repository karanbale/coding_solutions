/*
Given a number, check if its a power of 2 or not.
Note: You cannot use looping or branching.

Method 1:
Property to remember: 
    Number and its negative representation,
    both will always have right most set bit of the number set, all other 
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
#define POS_OF_ONLY_SET_BIT(x) (((x) & ((x)-1)))
#define ARR_LEN 6


int findRightmostSetBitInNumber(void){

    int num[ARR_LEN] = {5,4,1,0,8,12};

    for(int i=0; i<ARR_LEN; i++){
        // if ANDing of a number and its negative counterpart is equal to the number itself,
        // then given number is always power of 2
        printf("Position of right most set bit for Num: %d is: %d.\n", num[i], EVEN_ODD_METHOD_1(num[i])); 
    }

    return 0;
}

int findPositionOfOnlySetBitInNumber(void){

    int num[ARR_LEN] = {5,4,1,0,8,12};

    for(int i=0; i<ARR_LEN; i++){
        // if ANDing of a number and its negative counterpart is equal to 0, 
        // then it has only 1 set bit, other wise its invalid number
        if(POS_OF_ONLY_SET_BIT(num[i]) == 0){
        //if((num[i] & (num[i]-1)) == 0){
            printf("Position of only set bit for Num: %d is: %d.\n", num[i], (int)log2(num[i])+1);
            continue;
        }
        printf("This is invalid number.\n");
    }

    return 0;
}

int main(void){
    
  findRightmostSetBitInNumber();
  findPositionOfOnlySetBitInNumber();
  return 0;

}
