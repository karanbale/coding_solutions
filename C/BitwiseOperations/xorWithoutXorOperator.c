/*
Find XOR of two numbers without using XOR operator.

Method 1:
    Naive solution would be to compare every bit in same position for given numbers,
    and make a decision similar to that of XOR operator.

Method 2:
    We know following table for XOR / AND / OR gates.
    X   Y   XOR     OR     AND  ((X|Y) - (X&Y))
    0   0   0       0       0       0
    0   1   1       1       0       1
    1   0   1       1       0       1
    1   1   0       1       1       0
    
    As we can see, using expression ((x|y) - (x&y)) we obtain logical table same as of XOR.
    Thus we can simply use that.

*/

#include "../standardHeaders.h"

#define XOR(x,y) (((x)|(y)) - ((x)&(y)))

int main(void){

    int nums[4] = {64,65,66,67};

    for(int i=0; i<3; i++){
        printf("Num1: %d, Num2: %d, expected XOR: %d, observed XOR: %d\n", 
        nums[i], nums[i+1],(nums[i]^nums[i+1]), XOR(nums[i],nums[i+1]));
    }

    return 0;
}
