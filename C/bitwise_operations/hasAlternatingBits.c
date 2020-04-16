/*
Given a positive integer, check whether it has alternating bits: namely, 
if two adjacent bits will always have different values.

Example 1:
Input: 5
Output: True
Explanation:
The binary representation of 5 is: 101

Example 2:
Input: 7
Output: False
Explanation:
The binary representation of 7 is: 111.

Example 3:
Input: 11
Output: False
Explanation:
The binary representation of 11 is: 1011.

Example 4:
Input: 10
Output: True
Explanation:
The binary representation of 10 is: 1010.
*/

#include "utilities.h"

// following method wont work if you pass in INT32_MAX to it
// because unsigned int can only accomodate upto 32 int
int64_t int_to_bin(uint64_t k){
//    printf("K: %llu\n",k);
    return ((k == 0) ? 0 : ((k % 2) + 10 * int_to_bin(k / 2)));
}

bool hasAlternatingBits(int n){
    
    // for alternating bits number, if you right shift it by 1 then AND it with number itself, answer must be 0
    // for alternating bits number, if you right shift it by 2 then AND it with number itself, it must remain same as that of when you right shift it by 2 bits.
    return (((n & (n>>1)) == 0) && ((n & (n>>2)) == (n>>2)));
    
}

int main(void){
    int nums[] = {0,1,4,5,10,11,15};
    for(int i=0; i<7; i++){
        printf("Num: %d, Bin: %lld, Has alternating bits: %d\n", nums[i],int_to_bin(nums[i]), hasAlternatingBits(nums[i]));
    }
}
