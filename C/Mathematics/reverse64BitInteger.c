/*
Reverse a given 64 bit number.
*/

#include "mathematics_headers.h"

uint64_t reverse2(uint64_t v) {
    // swap odd and even bits
    v = ((v >> 1) & 0x5555555555555555) | ((v & 0x5555555555555555) << 1);
    // swap consecutive pairs
    v = ((v >> 2) & 0x3333333333333333) | ((v & 0x3333333333333333) << 2);
    // swap nibbles ... 
    v = ((v >> 4) & 0x0F0F0F0F0f0f0f0f) | ((v & 0x0F0F0F0F0f0f0f0f) << 4);
    // swap bytes
    v = ((v >> 8) & 0x00FF00FF00ff00ff) | ((v & 0x00FF00FF00ff00ff) << 8);
    // swap 2-byte long pairs
    v = ( v >> 16             ) | ( v               << 16);
    // swap 2-byte long pairs
    v = ( v >> 32             ) | ( v               << 32);
    return v;
}

uint64_t reverse1(uint64_t num) {
    uint8_t s = sizeof(num) * 8; // bit size; must be power of 2 
    uint64_t mask = ~0;         
    while ((s >>= 1) > 0) 
    {
      mask ^= (mask << s);
      num = ((num >> s) & mask) | ((num << s) & ~mask);
    }
    return num;
}

int main()
{
    int x = 10;
    int *const ptr = &x;
    // ptr = x;
    printf("Hello World %d, %d\n", *ptr, x);
    uint64_t num_arr[] = {INT32_MIN, INT64_MIN, INT32_MAX, INT64_MAX, 
        0x0, 0x3333333333333333, 0x1,
    };
    // uint64_t num1 = INT32_MIN-1;
    for(int i=0; i< sizeof(num_arr)/sizeof(num_arr[0]); i++) {
        printf("num1 original: 0x%016" PRIx64 "\n", num_arr[i]);
        num_arr[i] = reverse1(num_arr[i]);
        printf("num2 reversed: 0x%016" PRIx64 "\n", num_arr[i]);
        printf("num1 original: 0x%016" PRIx64 "\n", num_arr[i]);
        num_arr[i] = reverse2(num_arr[i]);
        printf("num2 reversed: 0x%016" PRIx64 "\n\n", num_arr[i]);
    }

    return 0;
}
