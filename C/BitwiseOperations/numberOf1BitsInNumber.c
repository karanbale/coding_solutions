/*
Write a function that takes an unsigned integer and return the number of '1' bits it has (also known as the Hamming weight).

Example 1:
Input: 00000000000000000000000000001011
Output: 3
Explanation: The input binary string 00000000000000000000000000001011 has a total of three '1' bits.

Example 2:
Input: 00000000000000000000000010000000
Output: 1
Explanation: The input binary string 00000000000000000000000010000000 has a total of one '1' bit.

Example 3:
Input: 11111111111111111111111111111101
Output: 31
Explanation: The input binary string 11111111111111111111111111111101 has a total of thirty one '1' bits.

*/

#include "utilities.h"

int hammingWeight_method1(uint32_t n) {
    long mask = 1;
    int count = 0;
    for(int i = 0; i < 32; ++i){ //31 will not do, delicate;
        if(mask & n) count++;
        mask <<= 1;
    }
    return count;
}

int hammingWeight_method2(uint32_t n) {
    if(n == 0) return 0;
    int count = 0;
    while(n){
        count++;
        n &= (n-1);
    }
    return count;
}

int main(void){

    // following numbers are: 43261596, 668
    uint32_t n[] = {0b00000010100101000001111010011100 , 0b00000000000000000000001010011100};

    for(int i =0; i<2; i++){
        printf("Num: %d, Total number of 1 bits method 1: %d, method 2: %d\n", n[i], hammingWeight_method1(n[i]),hammingWeight_method2(n[i]));
    }
    return 0;
}
