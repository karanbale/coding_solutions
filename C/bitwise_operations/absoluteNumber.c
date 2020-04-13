/*
So in practice "absolute value" means to remove any negative sign in front of a number, 
and to think of all numbers as positive (or zero). NO NEGATIVES !
The absolute value of −9 is 9
The absolute value of 3 is 3
The absolute value of 0 is 0
The absolute value of −156 is 156

Solution:
    If branching is not allowed, we can use following expression to compute absolute value.
    Expression: ((number + mask) ^ mask), where mask = (number >> 31)
    The mask (number >> 31) will be evaluated to 0 for positive numbers.
    The mask (number >> 31) will be evaluated to -1 for negative numbers.

Explanation:
    for positive integers, mask will be 0 and ((number + 0) ^ number) = number.
    for negative integers: mask will be -1 and ((numer + (-1)) ^ (-1)) = number.
        We know, we store negative of a number in 2's compliment form.
        i.e. we flip all the bits from its positive counterpart and add 1 to it.
        Now to get positive counterpart of a negative number, we substract 1 from it and
        flip its bits.

*/

#include "utilities.h"

#define MASK(x)     ((x) >> ((sizeof(int) * 8)-1))
#define ABS_VAL(x)  (((x)+(MASK(x))) ^ (MASK(x)))

int findAbsoluteNumber(int number){
    
    return ABS_VAL(number);

}

int main(void){

    int nums[6] = {1,5,-11,-22,INT32_MIN, INT32_MIN+2};
    for(int i=0; i<6; i++){
        printf("Num: %d Absolute Val: %d\n", nums[i], findAbsoluteNumber(nums[i]));
    }
    return 0;
}
