/*
Count the number of prime numbers less than a non-negative number, n.

Example 1:
Input: n = 10
Output: 4
Explanation: There are 4 prime numbers less than 10, they are 2, 3, 5, 7.

Example 2:
Input: n = 0
Output: 0

Example 3:
Input: n = 1
Output: 0

Constraints:

0 <= n <= 5 * 106

*/

#include "../standardHeaders.h"

int countPrimes(int n){
    
    if((n == 0) || (n == 1) || (n == 2)){
        return 0;
    }
    
    // lets assume all numbers present in array are prime and mark them as true
    bool primeNums[n+1];
    memset(primeNums, true, sizeof(primeNums));
    int sqrtOfN = sqrt(n);
    
    // for all perfect squares, set their respective values to false
    // start with index = 2, since 0 is not prime and 1 is neither prime, nor composite
    for(int i=2; i <= sqrtOfN; i++){
        // prime numbers are not even so let's remove all even numbers from consideration
        if((i%2 == 0) && (i>2)){
            primeNums[i] = false;
        }
        else if(primeNums[i] == true){
            // multiple of a perfect square numbers are not a prime numbers
            // so let's ignore them
            for(int j=(i*i); j<=n; j=j+i){
                primeNums[j] = false;
            }
        }
    }

    // At the end of this, only prime numbers will have prime_array[i] set to true.
    // Hence count those to get the result, Initializing count to 0
    int count = 0;
    
    // Start counting from prime number 2 and above as 0 is not prime.
    // 1 is neither prime nor composite
    for(int i=2; i<n; i++) {
        if(primeNums[i] == true) {
            count++;
        }
    }
    
    // Return the number of prime numbers less than n
    return count;
}