/*
Given a positive integer, check whether it has alternating bits: namely, 
if two adjacent bits will always have different values.

Example 1:
Input: 5 (0101)
num & (num >> 1) :
Num      = 0101
Num >> 1 = 0010
AND      = 0000   

num & (num >> 1) :
Num      = 0101
Num >> 2 = 0001
AND      = 0001   

Output: True
Explanation:
The binary representation of 5 is: 101

Example 2:
Input: 7 (0b 0111)
Output: False
Explanation:
The binary representation of 7 is: 111.

Example 3:
Input: 11 (0b 1011)
Output: False
Explanation:
The binary representation of 11 is: 1011.

Example 4:
Input: 10 (0b 1010)
Output: True
Explanation:
The binary representation of 10 is: 1010.
*/

#include "../standardHeaders.h"

// following method wont work if you pass in INT32_MAX to it
// because unsigned int can only accomodate upto 32 int
int64_t int_to_bin(uint64_t k){
//    printf("K: %llu\n",k);
    return ((k == 0) ? 0 : ((k % 2) + 10 * int_to_bin(k / 2)));
}

bool hasAlternatingBits(int n){
    
    // for alternating bits number, if you right shift it by 1 then AND it with number itself, answer must be 0
    // for alternating bits number, if you right shift it by 2 then AND it with number itself, 
    // it must remain same as that of when you right shift it by 2 bits.
    // e.g. take number 4 (0b 100), it will pass the condition ((n & (n-1)) == 0) 
    // but without next condition ((n & (n>>2)) == (n>>2)) it will be false positive
    return (((n & (n>>1)) == 0) && ((n & (n>>2)) == (n>>2)));
    
}

int main(void){
    int nums[] = {0,1,4,5,10,11,15};
    for(int i=0; i<7; i++){
        printf("Num: %d, Bin: %lld, Has alternating bits: %d\n", nums[i],int_to_bin(nums[i]), hasAlternatingBits(nums[i]));
    }
}
