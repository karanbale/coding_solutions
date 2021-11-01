#include "../standardHeaders.h"

int getProd(int a, int b){
    return (uintptr_t)&((char(*)[a])0x0)[b];
}

unsigned int russianPeasant(unsigned int a, unsigned int b) 
{ 
    int res = 0;  // initialize result 
  
    // While second number doesn't become 1 
    while (b > 0) 
    { 
         // If second number becomes odd, add the first number to result 
         if (b & 1) 
             res = res + a; 
  
         // Double the first number and halve the second number 
         a = a << 1; 
         b = b >> 1; 
     } 
     return res; 
} 

int main(void){

    int nums[4] = {1,2,3,4};
    for (int i = 0; i < 4; i=i+2)
    {
        printf("Sum of a: %d, b: %d is:\n",nums[i],nums[i+1]);
        printf("Method 1: %d\n",russianPeasant(nums[i], nums[i+1]));
        printf("Method 2: %d\n",getProd(nums[i], nums[i+1]));
        printf("\n");
    }
    return 0;
}
