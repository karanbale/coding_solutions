#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <stdarg.h>

unsigned int int_to_bin(unsigned int k) {
    return (k == 0 || k == 1 ? 0 : ((k % 2) + 10 * int_to_bin(k / 2)));
}

int onesComplement(int num){
    int lengthOfNum = (int) (log2(num)+1);
    printf("num: %d, len of num: %d\n", num, lengthOfNum);
    int bitmask = ((1<<lengthOfNum)-1);
    return (bitmask ^ num);
}

int main() 
{ 
    int x = 100, y = -100; 
    printf("Num: %d, Bits:%d, Flipped Bits: %d\n",x, int_to_bin(x), onesComplement(x));
    return 0; 
} 
