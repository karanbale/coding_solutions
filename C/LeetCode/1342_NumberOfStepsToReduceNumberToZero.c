/*
Given a non-negative integer num, return the number of steps to reduce it to zero. 
If the current number is even, you have to divide it by 2, otherwise, you have to subtract 1 from it.

Example 1:
Input: num = 14
Output: 6
Explanation: 
Step 1) 14 is even; divide by 2 and obtain 7. 
Step 2) 7 is odd; subtract 1 and obtain 6.
Step 3) 6 is even; divide by 2 and obtain 3. 
Step 4) 3 is odd; subtract 1 and obtain 2. 
Step 5) 2 is even; divide by 2 and obtain 1. 
Step 6) 1 is odd; subtract 1 and obtain 0.

Example 2:
Input: num = 8
Output: 4
Explanation: 
Step 1) 8 is even; divide by 2 and obtain 4. 
Step 2) 4 is even; divide by 2 and obtain 2. 
Step 3) 2 is even; divide by 2 and obtain 1. 
Step 4) 1 is odd; subtract 1 and obtain 0.

Example 3:
Input: num = 123
Output: 12

Constraints:
0 <= num <= 10^6
*/

#include "utilities.h"

/*
Method 1:

Property of Numbers:
    All odd numbers end with 1 in their binary representation.
    All even numbers end with 0 in their binary represenation.

    To reduce an even number to zero, we need to divide it by 2, until remainder is 0. 
        Only require 1 step operation.
    To reduce a odd number to zero, we need to substract 1 from it, to make it even, and then divide it by 2. 
        2 step opertaion.

    Thus we find out, number of 1s and number of 0's in given number and multiply it with above logic.
    Now remember, for MSB bit, we only need to substract 1 from it rather than dividing it again.
    Thus we substract 1 from final answer, to compensate for above statement.
*/

int numberOfSteps (int num){
    if(num == 0) return 0;
    
    // find total number of bits in given integer
    int totalNumBits = (int)log2(num)+1, totalOnes=0;
    
    // find total number of 1's in given num
    // aka find total even number of bits
    while(num){
        num &= (num-1);
        totalOnes++;
    }
    // printf("totalOnes: %d, totalBits: %d\n", totalOnes, totalNumBits);
    
    // it takes 2 steps to reduce even number and 1 step to reduce odd number
    // substract 1 from answer, since, for MSB 1 bit, we only need to reduce it once not twice
    return (((totalOnes * 2)+(totalNumBits - totalOnes))-1);
}

int main(void){

    int nums[] = {7,22,86};
    for(int i=0; i<3; i++){
        printf("Num: %d Steps to reduce to zero: %d\n", nums[i], numberOfSteps(nums[i]));
    }
    return 0;
}
