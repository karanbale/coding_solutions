/*
By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.

What is the 10,001st prime number?

URL: https://projecteuler.net/problem=7
*/

#include "mathematics_headers.h"

int main(void){
    
    uint32_t num = 1, prime_factor_index_count = 0;
    uint32_t num_sqrt = 0, prime_number = 0;
    const uint32_t prime_factor_index = 10001;

    // until we find the index we're looking for, don't stop
    while(prime_factor_index_count != prime_factor_index){

        // if number is divisible by 2, skip over it
        bool factor_found = false;
        if((num % 2) == 0){
            num++;
            continue;
        }

        for(int i=2; i< (sqrt(num)+1); i++){
            if((num % i) == 0){
                factor_found = true;
                break;
            }
        }
        if(!factor_found){
            // printf("Current Prime Num Found: %d\n", num);
            prime_factor_index_count++;
            prime_number = num;
        }
        num++;
    }

    printf("%d th Prime factor is: %d \n", prime_factor_index_count, prime_number);
    return 0;

}
