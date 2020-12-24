/*
Write a program to find the n-th ugly number.

Ugly numbers are positive numbers whose prime factors only include 2, 3, 5. 

Example:

Input: n = 10
Output: 12
Explanation: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 is the sequence of the first 10 ugly numbers.
Note:  

1 is typically treated as an ugly number.
n does not exceed 1690.`
*/

#include "../standardHeaders.h"

/**********************************************************************************************/
/******************************** Solution 1 **************************************************/
/**********************************************************************************************/

/**
 * @brief Method to find if given number n is an ugly number or not.
 * 
 * @param n number to be checked if it's ugly or not.
 * @return 1 if given number is ugly number, 0 otherwise
 */
int isUgly(int n){
    if(n == 0) return 0;
    int primeFactors[3] = {2,3,5};
    
    for(int i=0; i<3; i++){                     // divide number by 2, then 3, then 5
        while(n%primeFactors[i] == 0){          // repeatedly divide number until remainder is 0
            n = n/primeFactors[i];
        }
    }
    return n==1;
}

/**
 * @brief Method to find nth ugly number.
 * 
 * @param n nth ugly number to be found
 * @return nth ugly number found
 * @note This approach is a naïve brute force approach.
 *       For higher values of n, we will run into TLEs (Time limite exceeded)
 */
int nthUglyNumberSolution1(int n){
    int i = 0, count = 0;
    while(count != n){
        if(isUgly(++i)){
            count++;
        }
    }
    return i;
}

/**********************************************************************************************/
/******************************** Solution 2 **************************************************/
/**********************************************************************************************/

#define MIN(a,b) (((a) < (b)) ? (a) : (b))

/**
 * @brief Method to find nth ugly number
 * 
 * @param n nth ugly number to be found
 * @return nth ugly number that we found
 * 
 * @note    The algorithm is, we calculate first 1690 ugly numbers, using dynamic programming.
 *          The UB (Upper Bound) for n is 1690.
 *          Then we just return nth index from the array that hold 1690 ugly numbers.
 */
int nthUglyNumber(int n){
    size_t dp[1691];
    dp[0] = 1;
    int i2 = 0, i3 = 0, i5 = 0;
    for(int i=1; i<1690; i++){
        int tempUgly = MIN(dp[i2]*2, dp[i3]*3);
        dp[i] = MIN(tempUgly, dp[i5]*5);
        
        if(dp[i] == dp[i2]*2){
            i2 += 1;
        }
        if(dp[i] == dp[i3]*3){
            i3 += 1;
        }
        if(dp[i] == dp[i5]*5){
            i5 += 1;
        }
    }
    
    return dp[n-1];
}
