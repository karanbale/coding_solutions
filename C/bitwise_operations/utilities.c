#include "utilities.h"

// following method wont work if you pass in INT32_MAX to it
// because unsigned int can only accomodate upto 32 int
int64_t int_to_bin(uint64_t k){
//    printf("K: %llu\n",k);
    return ((k == 0) ? 0 : ((k % 2) + 10 * int_to_bin(k / 2)));
}

