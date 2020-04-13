/*
Reverse bits of a given 32 bits unsigned integer.

Example 1:

Input: 00000010100101000001111010011100
Output: 00111001011110000010100101000000
Explanation: The input binary string 00000010100101000001111010011100 represents the unsigned integer 43261596, 
so return 964176192 which its binary representation is 00111001011110000010100101000000.
Example 2:

Input: 11111111111111111111111111111101
Output: 10111111111111111111111111111111
Explanation: The input binary string 11111111111111111111111111111101 represents the unsigned integer 4294967293, 
so return 3221225471 which its binary representation is 10111111111111111111111111111111.
*/

#include "allHeaders.h"

// following method wont work if you pass in INT32_MAX to it
// because unsigned int can only accomodate upto 32 int
int64_t int_to_bin(uint64_t k) {
//    printf("K: %llu\n",k);
    return ((k == 0) ? 0 : ((k % 2) + 10 * int_to_bin(k / 2)));
}

/*
Static reverse table for 2 bits is as follows:
0 0 -> 0 ----> Reverse ----> 0 0 -> 0
0 1 -> 1 ----> Reverse ----> 1 0 -> 2
1 0 -> 2 ----> Reverse ----> 0 1 -> 1
1 1 -> 3 ----> Reverse ----> 1 1 -> 3

Now store these reversed values in an array and return them for its corresponding index values.
*/
const uint32_t rev2bit[] = { 0, 2, 1, 3 };

uint32_t reverseBits4(uint32_t n) {
    // Obtain upper nibble: right shifting n by 2 bits, then just OR it with lower nibble to store it
    // Obtain lower nibble: ANDing with last 2 bits, then reverse it, shift left by 2 bits
    // ORing lower nibble with reversed bits of itself and upper nibble, to get desired output
    return rev2bit[(n & 0x3)] << 2 | rev2bit[(n >> 2)];
}

uint32_t reverseBits8(uint32_t n) {
    // Obtain upper nibble: right shifting n by 4 bits, then just OR it with lower nibble to store it
    // Obtain lower nibble: ANDing with last 4 bits, reverse it further, shift left output by 4 bits
    // ORing lower nibble with reversed bits of itself and upper nibble, to get desired output
    return reverseBits4(n & 0xF) << 4 | reverseBits4(n >> 4);
}

uint32_t reverseBits16(uint32_t n) {
    // Obtain upper nibble: right shifting n by 8 bits, then just OR it with lower nibble to store it
    // Obtain lower nibble: ANDing with last 8 bits, reverse it further, shift left output by 8 bits
    // ORing lower nibble with reversed bits of itself and upper nibble, to get desired output
    return reverseBits8(n & 0xFF) << 8 | reverseBits8(n >> 8);
}

uint32_t reverseBits_Method1(uint32_t n) {
    // Obtain upper nibble: right shifting n by 16 bits, then just OR it with lower nibble to store it
    // Obtain lower nibble: ANDing with last 16 bits, reverse it further, shift left output by 16 bits
    // ORing lower nibble with reversed bits of itself and upper nibble, to get desired output
    return reverseBits16(n & 0xFFFF) << 16 | reverseBits16(n >> 16);
}

uint32_t reverseBits_Method2(uint32_t n) {
    unsigned int mask = 1<<31, res = 0;
    for(int i = 0; i < 32; ++i) {
        if(n & 1) res |= mask;
        mask >>= 1;
        n >>= 1;
    }
    return res;
}

uint32_t reverseBits_Method3(uint32_t n) {
	uint32_t mask = 1, ret = 0;
	for(int i = 0; i < 32; ++i){
		ret <<= 1;
		if(mask & n) ret |= 1;
		mask <<= 1;
	}
	return ret;
}

int main(void){

    // following numbers are: 43261596, 668
    uint32_t n[] = {0b00000010100101000001111010011100 , 0b00000000000000000000001010011100};
    // their reversed bits output is: 964176192, 960495616
    uint32_t expectedOutput[] = { 0b00111001011110000010100101000000, 0b00111001010000000000000000000000};

    for(int i =0; i<2; i++){
        printf("Number                : %lld\n", int_to_bin(n[i]));
        printf("Reversed bits Method 1: %d\n", reverseBits_Method1(n[i]));
        printf("Reversed bits Method 2: %d\n", reverseBits_Method2(n[i]));
        printf("Reversed bits Method 3: %d\n", reverseBits_Method3(n[i]));
        printf("\n");   // new line char
    }
    return 0;
}
