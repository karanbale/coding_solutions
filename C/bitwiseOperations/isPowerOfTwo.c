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

#include "utilities.h"

#define EVEN_ODD_METHOD_1(x) ((x)&(-(x)))
#define EVEN_ODD_METHOD_2(x) ((x)&((x)-1))
#define ARR_LEN 5

// following method wont work if you pass in INT32_MAX to it
// because unsigned int can only accomodate upto 32 int
int64_t int_to_bin(uint64_t k){
//    printf("K: %llu\n",k);
    return ((k == 0) ? 0 : ((k % 2) + 10 * int_to_bin(k / 2)));
}

int main(void){

    int num[ARR_LEN] = {5,4,1,0,8};

    printf("max pow value: %f\n", log2(INT32_MAX));
    printf("max value that is square of 2: %d\n",(int) pow(2, (int)log2(INT32_MAX)+1));

    for(int i=0; i<ARR_LEN; i++){
        // if ANDing of a number and its negative counterpart is equal to the number itself,
        // then given number is always power of 2
        
        // METHOD 1 & 2
        if(((EVEN_ODD_METHOD_1(num[i])) == num[i]) && (EVEN_ODD_METHOD_2(num[i])) == 0)  printf("Num: %d is power of 2.\n", num[i]);
        else printf("Num: %d is NOT power of 2.\n", num[i]);

        printf("num: %lld, negative num: %lld\n", int_to_bin(num[i]), int_to_bin(-num[i])); 

    }

    return 0;
}

