#include "utilities.h"

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

uint64_t toggleBits(uint64_t num){
    int lengthOfNum = (int) (log2(num)+1);
    int bitmask = ((1<<lengthOfNum)-1);
    printf("num: %lld, len of num: %d bitmask: %lld\n", num, lengthOfNum, int_to_bin(bitmask));
    return (bitmask ^ num);
}


int toggleBitsOfGivenNumber(void){ 
    int x = 100;
    printf("Num: %d, Bits:%lld, Flipped Bits: %lld\n", x, int_to_bin(x), int_to_bin(toggleBits(x)));
    x = 1024;
    printf("Num: %d, Bits:%lld, Flipped Bits: %lld\n", x, int_to_bin(x), int_to_bin(toggleBits(x)));
    // Convert 0xFFFF
    printf("Num: 65535, Bits:%lld, Flipped Bits: %lld\n", int_to_bin(65535), int_to_bin(toggleBits(65535)));
    // Convert 0xFFFFFF, following method fails for numbers larger than 65535
    // hence logging it here to display how it fails miserably
    printf("Num: 16777215, Bits:%lld, Flipped Bits: %lld\n", int_to_bin(16777215), int_to_bin(toggleBits(16777215)));
    // Cnvert 0xFFFFFFFF, following method fails for numbers larger than 65535
    // hence logging it here to display how it fails miserably
    printf("Num: 4294967295, Bits:%lld, Flipped Bits: %lld\n", int_to_bin(4294967295), int_to_bin(toggleBits(4294967295)));
    
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

    toggleBitsOfGivenNumber();
    return 0;
}

