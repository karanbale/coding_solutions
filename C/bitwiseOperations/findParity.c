/*
Parity refers to the number of 1s in a given number.
Odd parity (1) means there are odd number of 1s 
Even parity (0) means there are even number of 1s
Parity bits are often used as a crude means of error detection.

Method 1:
    A naive solution would be to calculate parity by chcking each bit of n one by one.
    The time taken is proportional to number of bits in the number.

Method 2:
    We can calculate parity by turning off the right most bit one by one and counting parity.
    The time taken is proportional to number of bits set, better than method 1.

    Number = 8
    (Num)    = 0b00001000 (8)
    (Num -1) = 0b00000111 (7)
    AND      = 0b00000000

    Number = 10
    (Num)       = 0b00001010 (10)
    (Num -1)    = 0b00001001 (9)
    AND         = 0b00001000 (8)
    now, AND it again with num-1 
    i.e. 7 since num is changed to 8 after previous ANDing
    AND (NUM-1) = 0b00000111 (7)
    AND         = 0b00000000 (0)

*/

#include "utilities.h"

#define TURN_OFF_RIGHT_MOST_SET_BIT(x) ((x) & (x-1))

// following method wont work if you pass in INT32_MAX to it
// because unsigned int can only accomodate upto 32 int
int64_t int_to_bin(uint64_t k){
//    printf("K: %llu\n",k);
    return ((k == 0) ? 0 : ((k % 2) + 10 * int_to_bin(k / 2)));
}

bool checkParityMethod1(int num){

    bool parity = false;
    while(num){
        if((num & 1) == 1){
            parity = !parity;
        }
        num = num >> 1;
    }

    return parity;
}

bool checkParityMethod2(int num){
    bool parity = false;

    while(num){
        parity = !parity;
        printf("num: %d Binary: %lld\n", num, int_to_bin(num));
        num = TURN_OFF_RIGHT_MOST_SET_BIT(num);        
    }

    return parity;
}

int main(void){

    int nums[5] = {0,1,5,8,22};
    for(int i=0; i<5; i++){
        printf("Num: %d \t Binary: %lld, \t Parity_Method 1: %d, Parity_Method 2: %d\n",
        nums[i], int_to_bin(nums[i]), checkParityMethod1(nums[i]), checkParityMethod2(nums[i]));
    }
    
    return 0;
}
