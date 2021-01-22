/*
Given an integer (signed 32 bits), write a function to check whether it is a power of 4.

Example 1:

Input: 16
Output: true

Example 2:
Input: 5
Output: false

Follow up: Could you solve it without loops/recursion?
*/

#include "utilities.h"
#define ARR_LEN 8

bool isPowerOfFour_method1(int num){
    
    long long x = num;
    return (((x & (x-1)) == 0) && ((x%3) == 1));
}


/*
METHOD 2 Explained:
Let's first check if num is a power of two: x > 0 and x & (x - 1) == 0.

Now the problem is to distinguish between even powers of two (when xx is a power of four) and 
odd powers of two (when xx is not a power of four). 

In binary representation both cases are single 1-bit followed by zeros.
What is the difference? 
In the first case (power of four), 1-bit is at even position: bit 0, bit 2, bit 4, etc. 
In the second case, at odd position: bit 1, bit 3, bit 5, bit 7 etc.

Case: Power of 4: 1 bit which is at even position i.e. bit 0, bit 2, bit 4, bit 6
x = 1    0 0 0 0 0 0 0 1
x = 4    0 0 0 0 0 1 0 0
x = 16   0 0 0 1 0 0 0 0
x = 64   0 1 0 0 0 0 0 0

Case: Power of 2, which is NOT power of 4: 1 bit which is at odd position i.e. bit 1, bit 3, bit 5, bit 7
x = 2     0 0 0 0 0 0 1 0
x = 8     0 0 0 0 1 0 0 0
x = 32    0 0 1 0 0 0 0 0
x = 128   1 0 0 0 0 0 0 0

Hence power of four would make a zero in a bitwise AND with number 0b101010...10:
4^a ^ (0b101010...10) == 0

How long should be (101010...10)_2
if xx is a signed integer? 32 bits. To write shorter, in 8 charaters instead of 32, 
it's common to use hexadecimal representation: 0b101010...10 = 0xaaaaaaaa

​x & (0xaaaaaaaa) ==0

Complexity Analysis:

Time complexity : O(1).
Space complexity : O(1).

*/
bool isPowerOfFour_method2(int num){
    
    long long x = num;
    return (num > 0) && ((num & (num - 1)) == 0) && ((num & 0xaaaaaaaa) == 0);
}

int main(void){

    int num[ARR_LEN] = {5,4,1,0,8,16,32,128};

    for(int i=0; i<ARR_LEN; i++){
        
        if(isPowerOfFour_method1(num[i]) && isPowerOfFour_method2(num[i]))  printf("Num: %d is power of 4.\n", num[i]);
        else printf("Num: %d is NOT power of 3.\n", num[i]);

    }

    return 0;
}
