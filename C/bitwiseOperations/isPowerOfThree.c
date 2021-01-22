/*
Given an integer, write a function to determine if it is a power of three.

Example 1:
Input: 27
Output: true

Example 2:
Input: 0
Output: false

Example 3:
Input: 9
Output: true

Example 4:
Input: 45
Output: false
*/

#include "utilities.h"
#define ARR_LEN 5

bool isPowerOfThree(int n){
    
    // if n <= 0 just return false
    if(n <= 0) return false;

    // 1 is power of 3, 3^0 = 1
    if(n == 1) return true;
    
    // Divide n by 3 repeatedly, until only 3 is left
    while(n>3){
        if(n%3 != 0) return false;
        n = n/3;
    }
    // if n == 3, we were able to devide n by 3
    if(n == 3) return true;

    // otherwise, we failed, return false.
    return false;

}
int main(void){

    int num[ARR_LEN] = {5,4,1,0,8};

    printf("max pow value: %f\n", log2(INT32_MAX));
    printf("max value that is square of 2: %d\n",(int) pow(2, (int)log2(INT32_MAX)+1));

    for(int i=0; i<ARR_LEN; i++){
        
        if(isPowerOfThree(num[i]))  printf("Num: %d is power of 3.\n", num[i]);
        else printf("Num: %d is NOT power of 3.\n", num[i]);

    }

    return 0;
}