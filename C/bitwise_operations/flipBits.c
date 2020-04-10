#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <stdarg.h>

int binary_num[32] = {0};

void flush_binary_num_array(void){
    for(int i=0; i<32; i++){
        binary_num[i] = 0;
    }
}

// following method wont work if you pass in INT32_MAX to it
// because unsigned int can only accomodate upto 32 int
int64_t int_to_bin(uint64_t k) {
//    printf("K: %llu\n",k);
    return ((k == 0) ? 0 : ((k % 2) + 10 * int_to_bin(k / 2)));
}

int int_to_bin_array(uint64_t k) {
    static int i = 32;
//    printf("K: %llu k mod 2: %llu \n",k, (k%2));
    binary_num[i--] = (k % 2);
    return ((k == 0) ? 0 : int_to_bin_array(k/2));
}

uint64_t flipBits(uint64_t num){
    int lengthOfNum = (int) (log2(num)+1);
    printf("num: %lld, len of num: %d\n", num, lengthOfNum);
    int bitmask = ((1<<lengthOfNum)-1);
    return (bitmask ^ num);
}

int flipBitsForGivenNumber(void){ 
    int x = 100, y = -100; 
    // Convert 0xFFFF
    printf("Num: 65535, Bits:%lld, Flipped Bits: %lld\n", int_to_bin(65535), int_to_bin(flipBits(65535)));
    // Convert 0xFFFFFF
    printf("Num: 16777215, Bits:%lld, Flipped Bits: %lld\n", int_to_bin(16777215), int_to_bin(flipBits(16777215)));
    // Cnvert 0xFFFFFFFF 
    printf("Num: 4294967295, Bits:%lld, Flipped Bits: %lld\n", int_to_bin(4294967295), int_to_bin(flipBits(4294967295)));
    
    int array_size = 3;
    uint64_t nums_array[3] = {65535,16777215, INT32_MAX};
    for(int i=0; i<array_size; i++){
        int_to_bin_array(nums_array[i]);
        printf("num: %lld, bin:",nums_array[i]);
        for(int i=0; i<32; i++){
            printf("%d", binary_num[i]);
        }
        printf("\n");
        flush_binary_num_array();
    }
    
    return 0; 
} 

int main(void){

    flipBitsForGivenNumber();
    return 0;
}

