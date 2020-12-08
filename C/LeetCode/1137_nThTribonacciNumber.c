/*
The Tribonacci sequence Tn is defined as follows: 
T0 = 0, T1 = 1, T2 = 1, and Tn+3 = Tn + Tn+1 + Tn+2 for n >= 0.
Given n, return the value of Tn. 

Example 1:
Input: n = 4
Output: 4
Explanation:
T_3 = 0 + 1 + 1 = 2
T_4 = 1 + 1 + 2 = 4

Example 2:
Input: n = 25
Output: 1389537
 
Constraints:

0 <= n <= 37
The answer is guaranteed to fit within a 32-bit integer, ie. answer <= 2^31 - 1.
*/

#include "../standardHeaders.h"


int tribonacci(int n){    
    if(n == 0){
        return 0;
    }
    
    size_t f[] = {[0]=0, [1]=1, [2]=1, [3]=2};
    
    // calculate F[3] as given then just shift values of remaining positions
    // assign f[1] to f[0]
    // then assign f[2] to f[1]
    // then assign f[3] to f[2]
    // run this in recursive loop, N-1 times
    for(int i=1; f[3]=f[2]+f[1]+f[0], f[0]=f[1], f[1]=f[2], f[2]=f[3], i<n; i++);
    
//     printf("N:%d\n",n);
//     printf("F[0]: %ld\n", f[0]);
//     printf("F[1]: %ld\n", f[1]);
//     printf("F[1]: %ld\n", f[2]);
//     printf("\n");
    
    return f[0];
    
}

