/*
Check if adjacent bits are set in binary representation of a given number.

Method 1:
    Naive solution would be to consider every bit present in the number one by one and 
    compare it with its previous bit. If current bit and previous bit both are 1, then we have
    found a pair with adjacent bits as 1.

Method 2:
    We right shift or left shift the number as step 1.
    Then we compare given number with this right/left shifted number.
    If outout is 0, then there are no pair with adjacent 1's.
    If output is greater than 0, then there are pair with adjacent 1's.

    Number WITH adjacent pair of 1's
    Number    : 67
    Binary    : 0b01000011
    Number<<1 : 0b10000110
    ANDing O/P: 0b00000010

    Number WITHOUT adjacent pair of 1's
    Number    : 64
    Binary    : 0b01000000
    Number<<1 : 0b10000000
    ANDing O/P: 0b00000000
*/

#include "utilities.h"

bool checkBitsLefthift(int number){
    printf("Num: %d, (num<<1): %d\n", number, (number<<1));
    return ((number)&(number<<1));
}

bool checkBitsRightShift(int number){
    printf("Num: %d, (num>>1): %d\n", number, (number>>1));
    return ((number)&(number>>1));
}

int main(void){

    int nums[3] = {3,64,67};
    for(int i=0; i<3; i++){
        if(checkBitsLefthift(nums[i]) && checkBitsRightShift(nums[i])) 
            printf("Num: %d has adjacent pair of 1s\n",nums[i]);
        else printf("Num: %d has NO adjacent pair of 1s\n",nums[i]);
    }
    return 0;
}

