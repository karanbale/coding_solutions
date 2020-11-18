/*

Determine whether an integer is a palindrome. An integer is a palindrome when it reads the same backward as forward.

Follow up: Could you solve it without converting the integer to a string?

Example 1:

Input: x = 121
Output: true
Example 2:

Input: x = -121
Output: false
Explanation: From left to right, it reads -121. From right to left, it becomes 121-. Therefore it is not a palindrome.
Example 3:

Input: x = 10
Output: false
Explanation: Reads 01 from right to left. Therefore it is not a palindrome.
Example 4:

Input: x = -101
Output: false

Constraints:

-231 <= x <= 231 - 1

*/

#include "../standardHeaders.h"

size_t reverseInteger(int x){
    
    size_t retNum = 0, temp = 0;
    while(x){
        retNum = (retNum*10) + (x%10);
        if(retNum > INT32_MAX) return 0;
        x = x/10;
    }
    return retNum;
    
}

bool isPalindrome(int x){
    
    if((x > INT32_MAX) || (x < INT32_MIN) || (x < 0)) return false;
    
    if( x == reverseInteger(x)) return true;
    
    return false;

}

/*

Sample inputs to test:
121
-312
1534236469
-2147483648
2147483647
6767676
22222222
10

*/