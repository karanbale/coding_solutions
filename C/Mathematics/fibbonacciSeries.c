/*
The Fibonacci numbers, commonly denoted F(n) form a sequence, called the Fibonacci sequence, 
such that each number is the sum of the two preceding ones, starting from 0 and 1. That is,

F(0) = 0,   F(1) = 1
F(N) = F(N - 1) + F(N - 2), for N > 1.
Given N, calculate F(N).

Example 1:
Input: 2
Output: 1
Explanation: F(2) = F(1) + F(0) = 1 + 0 = 1.

Example 2:
Input: 3
Output: 2
Explanation: F(3) = F(2) + F(1) = 1 + 1 = 2.

Example 3:
Input: 4
Output: 3
Explanation: F(4) = F(3) + F(2) = 2 + 1 = 3.

Note:

0 ≤ N ≤ 30.
*/

#include "mathematics_headers.h"

int fib(int N){
    
    // create an array with values initialized as 0,1,0
    // i.e. f[] = [0,1,0]
    int f[] = {[0]=0, [1] = 1, [2] = 0};
    
    // for each iteration, do following and reduce N by 1
    // f[2] = f[0] + f[1]   ==> take sum of f[0] and f[1]
    // f[0] = f[1]          ==> shift f[1] to f[0]
    // f[2] = f[2]          ==> shift f[2] to f[1]
    for(; N; f[2] = f[1]+f[0], f[0] = f[1], f[1]=f[2], N--);
    
    // return the last value that you've calculated, which is at f[0]
    return f[0];

}
