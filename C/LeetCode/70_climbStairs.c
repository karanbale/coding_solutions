/*
You are climbing a staircase. It takes n steps to reach the top.
Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?

Example 1:

Input: n = 2
Output: 2
Explanation: There are two ways to climb to the top.
1. 1 step + 1 step
2. 2 steps

Example 2:
Input: n = 3
Output: 3
Explanation: There are three ways to climb to the top.
1. 1 step + 1 step + 1 step
2. 1 step + 2 steps
3. 2 steps + 1 step

Constraints:

1 <= n <= 45
*/

#include "../standardHeaders.h"

int climbStairs(int n){
    // create an array with values initialized as 0,1,0
    // i.e. f[] = [0,1,0]
    size_t f[] = {[0]=1, [1] = 2, [2] = 0};
    
    // for each iteration, do following
    // calculate F[2] as given then just shift values of remaining positions
    // assign f[1] to f[0]
    // then assign f[2] to f[1]
    // run this in recursive loop, N-1 times

    // NOTE: We need to increment i from 1 to n pr 0 to n-1
    // because, when we create the array, we have done first addition already
    // i.e. we've added 1 and 2 to the fibbonacci series and that's first number
    for(int i=1; i<n; i++){
        f[2] = f[0] + f[1];   //==> take sum of f[0] and f[1]
        f[0] = f[1];          //==> shift f[1] to f[0]
        f[1] = f[2];          //==> shift f[2] to f[1]

        printf("N:%d\n",n);
        printf("F[0]: %ld\n", f[0]);
        printf("F[1]: %ld\n", f[1]);
        printf("F[1]: %ld\n", f[2]);
        printf("\n");
    }
    
    // return the last value that you've calculated, which is at f[0]
    return f[0];

}
