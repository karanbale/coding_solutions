/*

Given two integers dividend and divisor, divide two integers without using multiplication, division, and mod operator.
Return the quotient after dividing dividend by divisor.
The integer division should truncate toward zero, which means losing its fractional part. For example, truncate(8.345) = 8 and truncate(-2.7335) = -2.

Note: Assume we are dealing with an environment that could only store integers within the 32-bit signed integer range: [−231, 231 − 1].
For this problem, assume that your function returns 231 − 1 when the division result overflows.

Example 1:

Input: dividend = 10, divisor = 3
Output: 3
Explanation: 10/3 = truncate(3.33333..) = 3.
Example 2:

Input: dividend = 7, divisor = -3
Output: -2
Explanation: 7/-3 = truncate(-2.33333..) = -2.
Example 3:

Input: dividend = 0, divisor = 1
Output: 0
Example 4:

Input: dividend = 1, divisor = 1
Output: 1
 

Constraints:

-231 <= dividend, divisor <= 231 - 1
divisor != 0

*/

#include "../standardHeaders.c"

int divide(int dividend, int divisor){
    int flag = 0;
    int result = 0;
    long temp = 0, m = 0;
    
    if((dividend==INT_MIN) && (divisor==-1))
        return INT_MAX;
    if(divisor == 1)
        return dividend;
    
    if((dividend ^ divisor) < 0)
        flag = -1;

    // handle the INT_MIN which can't use abs
    if(dividend==INT_MIN)
    {
        if(divisor==INT_MIN)
            return 1;
        divisor = abs(divisor);
        dividend += divisor;
        result = 1;
    }
    // dividend is not INT_MIN, while divisor is, result 0
    else if(divisor==INT_MIN)
    {
        return 0;
    }
    
    dividend = abs(dividend);
    divisor = abs(divisor);
    
    // when there is more to calculate 
    while(dividend >= divisor)
    {
        // start from the divisor
        temp = divisor;
        m = 1;
        while(dividend >= temp)
        {
            //shift the temp divisor until it's bigger than the dividend
            temp = temp << 1;
            // remember the temporary result
            m = m << 1;
        }
        
        // substract the temp divisor from total
        dividend = dividend - (temp >> 1);
        // add up the temporary result
        result += (m >> 1);
    }
    
    if(flag == -1)
        return -result;
    else
        return result;
}
