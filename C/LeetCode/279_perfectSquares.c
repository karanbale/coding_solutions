/*
Given a positive integer n, find the least number of perfect square numbers (for example, 1, 4, 9, 16, ...),
which sum to n.

Example 1:
Input: n = 12
Output: 3 
Explanation: 12 = 4 + 4 + 4.

Example 2:
Input: n = 13
Output: 2
Explanation: 13 = 4 + 9.
*/

#include "../standardHeaders.h"

#define MIN(x,y) ((x) < (y) ? (x) : (y))

/**********************************************************************************************/
/******************************** Solution 1 **************************************************/
/**********************************************************************************************/

/**
 * @brief Method to find minimum number of perfect squares those add up to given integer n
 * 
 * @param n Input Ingeter n 
 * @return number of perfect squares which add up to n
 * 
 * @note Solution using dynamic programming. Take a dp array, initialize it to INT32_MAX.
 * Take another array namely, sqrtArr and calculate all the perfect squares from 0 upto sqrt(n).
 * Only calculate upto sqrt(n) because after that, we cannot have a perfect square that add up to n.
 * e.g. for n = 16, sqrt(16) = 4, and perfect square of 5 = 25, is greater than 16, so is not useful.
 * 
 * For each number, we can add a perfect square of 1 up to number, so max addition of perfect squares can be: n
 * e.g. 5 = 1^2 + 1^2 + 1^2 + 1^2 + 1^2
 * Thus initialize dp[i] = i
 * Next lets substract each possible perfect square from sqrtArr from i and see how many such combinations we need
 * to obtain number n.
 * We will eventually go up to dp[1] = 1, where we'll return 1.
 * 
 * e.g. 
 * n = 4
 * dp    = | 0 | 1 | 2 | 3 | 4 |
 * Index = | 0 | 1 | 2 | 3 | 4 |
 * We can add each number in dp using perfect square given number of times, upto n=3
 * for n=4, we can add it using 1^2 * 4, or since its a perfect square of 2, just use it once.
 * Thus new dp will become:
 * dp    = | 0 | 1 | 2 | 3 | 1 |
 * Index = | 0 | 1 | 2 | 3 | 4 |
 * 
 */
int numSquaresSolution1(int n){
    
    int sqrtOfN = (sqrt(n)+1);
    int sqrtArr[sqrtOfN];
    int dp[n+1];
    for(int i=0; i<sqrtOfN; i++){
        sqrtArr[i] = i*i;
    }
    dp[0] = 0;
    
    for(int i=1; i<n+1; i++){
        dp[i] = i;
        for(int j=1; j<sqrtOfN; j++){       // iterate over sqrtArr array
            if(i < sqrtArr[j]){             // current perfect square is > number i, no need to continue, go to next i
                break;
            }
            dp[i] = MIN(dp[i], 1+dp[i-sqrtArr[j]]);
        }
    }
    
    return dp[n];
}


/**********************************************************************************************/
/******************************** Solution 2 **************************************************/
/**********************************************************************************************/

/**
 * @brief Method to find minimum number of perfect squares those add up to given integer n
 * 
 * @param n Input Ingeter n 
 * @return number of perfect squares which add up to n
 * 
 * @note    This is a brute force method and will run into TLE (Time limit exceeded).
 *          We need to improve this algorithm, refer to Solution 1 for DP approach.
 */
int solve(int n){
    if(n == 0)  return 0;
    if(n == 1)  return 1;
    int ans = INT32_MAX;
    for(int i=1; i*i <= n; i++){
        if(n < i*i){
            break;
        }
        ans = MIN(ans, 1+solve(n-i*i));
    }
    return ans;
}

int numSquaresSolution2(int n){
    return solve(n);
}

/**********************************************************************************************/
/******************************** Solution 3 **************************************************/
/**********************************************************************************************/

/**
 * @brief Method to find minimum number of perfect squares those add up to given integer n
 * 
 * @param n Input Ingeter n 
 * @return number of perfect squares which add up to n
 * 
 * @note:   This method uses two theorems: Legendre's 4 squares and Legendre's 3 square theorem.
 * According to Legendre's theorem, a number can have only upto 4 perfect squares those add up to number.
 * You can never have more than 4 perfect squares those add up to number n.
 * 
 * Legendre's 4 square Theorem:
 *      This theorem states that, any natural number n, can be represented as a sum of 4 perfect square numbers.
 *      e.g. n = a^2 + b^2 + c^2 + d^2
 * 
 * Legendre's 3 square Theorem:
 *      This theorem states that, any natural number n, cab be represented as a sum of 3 perfect square numbers,
 *      as long as this number n is not of the form 4^k(8*m + 7) where k and m are non-negative integers.
 *      e.g. n = a^2 + b^2 + c^2 .... for all n != 4^k(8*m + 7)
 * 
 * Perfect Square theorem 1:
 *      A square root of a perfect square is always perfect square. e.g. √16 = 4 is perfect square of 2
 *      Thus if we find a number n such that it is a perfect square, then there is only 1 such number, so return 1.
 * 
 * Perfect Square theorem 2:
 *      A square root of muliplication of two perfect square numbers always yields multiplication of perfect squares.
 *      e.g. √a*a * b*b = a*b
 * 
 * 
 */
int numSquares(int n) {
    while (n % 4 == 0)              // Legendre's 3 square theorem, calculate 4^k, keep dividing n by 4, until remainder is not 0
        n /= 4;
    if (n % 8 == 7)                 // Legendre's 3 square theorem, if n mod 8 yeilds remainder 7, then n is of form 4^k(8*m + 7)
        return 4;                   // thus we definitely will have more than 3 perfect squares, return 4
    for (int a=0; a*a<=n; ++a) {    // iterate over n in brute force manner 
        int b = sqrt(n - a*a);      // check if number - perfect square yeilds a perfect square for us
        if (a*a + b*b == n)         
            return 1 + !!a;         // if a == 0, return 1, otherwise return 2
    }
    return 3;                       // we know a number cannot have 1,2 or 4 perfect squares, so it must be 3, just return it
}
