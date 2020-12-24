/*
Write a program to find the nth super ugly number.

Super ugly numbers are positive numbers whose all prime factors are in the given prime list primes of size k.

Example:
Input: n = 12, primes = [2,7,13,19]
Output: 32 
Explanation: [1,2,4,7,8,13,14,16,19,26,28,32] is the sequence of the first 12 
             super ugly numbers given primes = [2,7,13,19] of size 4.
Note:

1 is a super ugly number for any given primes.
The given numbers in primes are in ascending order.
0 < k ≤ 100, 0 < n ≤ 106, 0 < primes[i] < 1000.
The nth super ugly number is guaranteed to fit in a 32-bit signed integer.
*/

#include "../standardHeaders.h"

int nthSuperUglyNumber(int n, int* primes, int primesSize){

    int i, j, min;
    int u[1000]={0,}, last[100]={0,};
    u[0] = 1;
    for(i=1; i<n; i++)
    {
        u[i] = u[last[0]]*primes[0];
        for(j=1; j<primesSize; j++)
        {
            min = primes[j]*u[last[j]];
            u[i] = u[i]<min ? u[i]:min ;
        }
        for(j=0; j<primesSize; j++)
            if(u[i] == primes[j]*u[last[j]]){
                last[j]++;
            }
    }
    min = u[n-1];
    return min;
}

